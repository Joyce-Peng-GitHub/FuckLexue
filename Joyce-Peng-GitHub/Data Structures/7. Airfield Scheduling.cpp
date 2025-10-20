#include <bits/stdc++.h>

inline void redirectIO() {
#ifndef ONLINE_JUDGE
	char filename[] = __FILE__;
	filename[sizeof(filename) - 4] = 'i';
	filename[sizeof(filename) - 3] = 'n';
	filename[sizeof(filename) - 2] = '\0';
	std::freopen(filename, "r", stdin);
	filename[sizeof(filename) - 4] = 'o';
	filename[sizeof(filename) - 3] = 'u';
	filename[sizeof(filename) - 2] = 't';
	std::freopen(filename, "w", stdout);
#endif
}

class Airfield {
public:
	struct Request {
		uint64_t tm, plane_id;

		Request() = default;
		Request(uint64_t tm, uint64_t plane_id) : tm(tm), plane_id(plane_id) {}

		friend bool operator<(const Request &lhs, const Request &rhs) {
			return ((lhs.tm == rhs.tm) ? (lhs.plane_id < rhs.plane_id) : (lhs.tm < rhs.tm));
		}
		friend bool operator>(const Request &lhs, const Request &rhs) {
			return ((lhs.tm == rhs.tm) ? (lhs.plane_id > rhs.plane_id) : (lhs.tm > rhs.tm));
		}
	};
	struct Statistics {
		size_t runway_num;
		uint64_t tot_tm;
		uint64_t tot_landing_q_tm, tot_takeoff_q_tm;
		uint64_t landing_cnt, takeoff_cnt;
		const uint64_t *runway_tot_busy_tm;

		Statistics() = default;
		Statistics(size_t runway_num, uint64_t tot_tm,
				   uint64_t tot_landing_q_tm, uint64_t tot_takeoff_q_tm,
				   uint64_t landing_cnt, uint64_t takeoff_cnt,
				   const uint64_t *runway_tot_busy_tm)
			: runway_num(runway_num), tot_tm(tot_tm),
			  tot_landing_q_tm(tot_landing_q_tm), tot_takeoff_q_tm(tot_takeoff_q_tm),
			  landing_cnt(landing_cnt), takeoff_cnt(takeoff_cnt), runway_tot_busy_tm(runway_tot_busy_tm) {}

		void print() const noexcept {
			std::printf("simulation finished\n"
						"simulation time: %4" PRIu64 "\n"
						"average waiting time of landing: %4.1lf\n"
						"average waiting time of takeoff: %4.1lf\n",
						tot_tm - 1,
						static_cast<double>(tot_landing_q_tm) / landing_cnt,
						static_cast<double>(tot_takeoff_q_tm) / takeoff_cnt);
			uint64_t tot_busy_tm = 0;
			for (size_t i = 0; i < runway_num; ++i) {
				tot_busy_tm += runway_tot_busy_tm[i];
				printf("runway %02zu busy time: %4" PRIu64 "\n", i + 1, runway_tot_busy_tm[i]);
			}
			printf("runway average busy time percentage: %4.1lf%%\n", tot_busy_tm * 100.0 / ((tot_tm - 1) * runway_num));
		}
	};

	using PriorityQueue = std::priority_queue<Request, std::vector<Request>, std::greater<Request>>;

	Airfield(uint64_t landing_duration, uint64_t takeoff_duration,
			 size_t runway_num)
		: m_landing_duration(landing_duration), m_takeoff_duration(takeoff_duration),
		  m_runway_num(runway_num),
		  m_runway_occupation_end_tm(new uint64_t[runway_num]{0}),
		  m_runway_tot_busy_tm(new uint64_t[runway_num]{0}) {
		for (size_t i = 0; i < runway_num; ++i) {
			m_free_runways.emplace_hint(m_free_runways.end(), i);
		}
	}

	bool isEmpty() const noexcept {
		return (m_free_runways.size() == m_runway_num &&
				m_landing_requests.empty() && m_takeoff_requests.empty());
	}

	bool simulate(uint64_t landing_requests_num, uint64_t takeoff_requests_num) {
		printf("Current Time: %4" PRIu64 "\n", m_cur_tm);
		if (m_cur_tm) m_checkRunways();
		m_addLandingRequests(landing_requests_num);
		m_addTakeoffRequests(takeoff_requests_num);
		m_handleRequests();
		++m_cur_tm;
		return isEmpty();
	}

	Statistics getStatistics() const noexcept {
		return Statistics(m_runway_num, m_cur_tm,
						  m_tot_landing_q_tm, m_tot_takeoff_q_tm,
						  m_landing_cnt, m_takeoff_cnt,
						  m_runway_tot_busy_tm.get());
	}

protected:
	uint64_t m_landing_duration, m_takeoff_duration;
	uint64_t m_cur_tm = 0;
	size_t m_runway_num;
	std::unique_ptr<uint64_t[]> m_runway_occupation_end_tm, m_runway_tot_busy_tm;
	std::set<size_t> m_free_runways;
	uint64_t m_landing_cnt = 0, m_takeoff_cnt = 0;
	uint64_t m_tot_landing_q_tm = 0, m_tot_takeoff_q_tm = 0;
	PriorityQueue m_landing_requests, m_takeoff_requests;

	void m_setFreeRunway(size_t id) {
		m_free_runways.emplace(id);
		std::printf("runway %02zu is free\n", id + 1);
	}
	void m_checkRunway(size_t id) {
		if (m_runway_occupation_end_tm.get()[id] == m_cur_tm) m_setFreeRunway(id);
	}
	void m_checkRunways() {
		for (size_t i = 0; i < m_runway_num; ++i) m_checkRunway(i);
	}

	void m_addRequests(size_t n, PriorityQueue &pq, uint64_t &cnt) {
		while (n--) pq.emplace(m_cur_tm, cnt++);
	}
	void m_addLandingRequests(size_t n) {
		m_addRequests(n, m_landing_requests, m_landing_cnt);
	}
	void m_addTakeoffRequests(size_t n) {
		m_addRequests(n, m_takeoff_requests, m_takeoff_cnt);
	}

	void m_handleLanding(const Request &request) {
		m_tot_landing_q_tm += m_cur_tm - request.tm;

		auto runway_id = *m_free_runways.begin();
		m_free_runways.erase(m_free_runways.begin());
		m_runway_tot_busy_tm.get()[runway_id] += m_landing_duration;
		m_runway_occupation_end_tm.get()[runway_id] = m_cur_tm + m_landing_duration;

		std::printf("airplane %04" PRIu64 " is ready to land on runway %02zu\n", request.plane_id + 5001, runway_id + 1);
	}
	void m_handleTakeoff(const Request &request) {
		m_tot_takeoff_q_tm += m_cur_tm - request.tm;

		auto runway_id = *m_free_runways.begin();
		m_free_runways.erase(m_free_runways.begin());
		m_runway_tot_busy_tm.get()[runway_id] += m_takeoff_duration;
		m_runway_occupation_end_tm.get()[runway_id] = m_cur_tm + m_takeoff_duration;

		std::printf("airplane %04" PRIu64 " is ready to takeoff on runway %02zu\n", request.plane_id + 1, runway_id + 1);
	}
	void m_handleLandingRequests() {
		while (m_free_runways.size() && m_landing_requests.size()) {
			m_handleLanding(m_landing_requests.top());
			m_landing_requests.pop();
		}
	}
	void m_handleTakeoffRequests() {
		while (m_free_runways.size() && m_takeoff_requests.size()) {
			m_handleTakeoff(m_takeoff_requests.top());
			m_takeoff_requests.pop();
		}
	}
	void m_handleRequests() {
		m_handleLandingRequests();
		m_handleTakeoffRequests();
	}

private:
};

std::unique_ptr<Airfield> p_af;

inline void preprocess() {
	size_t runway_num;
	uint64_t landing_duration, takeoff_duration;
	std::scanf("%zu%" SCNu64 "%" SCNu64, &runway_num, &landing_duration, &takeoff_duration);
	p_af.reset(new Airfield(landing_duration, takeoff_duration, runway_num));
}

int mainLoop() {
	int64_t landing_requests, takeoff_requests;
	while (true) {
		std::scanf("%" SCNd64 "%" SCNd64, &landing_requests, &takeoff_requests);
		p_af->simulate(std::max(int64_t(0), landing_requests),
					   std::max(int64_t(0), takeoff_requests));
		if (landing_requests < 0 && takeoff_requests < 0) break;
	}
	while (!p_af->isEmpty()) p_af->simulate(0, 0);
	p_af->getStatistics().print();
	return 0;
}

int main() {
	redirectIO();
	preprocess();
	return mainLoop();
}