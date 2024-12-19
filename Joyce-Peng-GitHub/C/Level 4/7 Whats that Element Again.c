// 神经病题目
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char elements[][50] = {
	"H,Hydrogen",
	"He,Helium",
	"Li,Lithium",
	"Be,Beryllium",
	"B,Boron",
	"C,Carbon",
	"N,Nitrogen",
	"O,Oxygen",
	"F,Fluorine",
	"Ne,Neon",
	"Na,Sodium",
	"Mg,Magnesium",
	"Al,Aluminum",
	"Si,Silicon",
	"P,Phosphorus",
	"S,Sulfur",
	"Cl,Chlorine",
	"Ar,Argon",
	"K,Potassium",
	"Ca,Calcium",
	"Sc,Scandium",
	"Ti,Titanium",
	"V,Vanadium",
	"Cr,Chromium",
	"Mn,Manganese",
	"Fe,Iron",
	"Co,Cobalt",
	"Ni,Nickel",
	"Cu,Copper",
	"Zn,Zinc",
	"Ga,Gallium",
	"Ge,Germanium",
	"As,Arsenic",
	"Se,Selenium",
	"Br,Bromine",
	"Kr,Krypton",
	"Rb,Rubidium",
	"Sr,Strontium",
	"Y,Yttrium",
	"Zr,Zirconium",
	"Nb,Niobium",
	"Mo,Molybdenum",
	"Tc,Technetium",
	"Ru,Ruthenium",
	"Rh,Rhodium",
	"Pd,Palladium",
	"Ag,Silver",
	"Cd,Cadmium",
	"In,Indium",
	"Sn,Tin",
	"Sb,Antimony",
	"Te,Tellurium",
	"I,Iodine",
	"Xe,Xenon",
	"Cs,Cesium",
	"Ba,Barium",
	"La,Lanthanum",
	"Ce,Cerium",
	"Pr,Praseodymium",
	"Nd,Neodymium",
	"Pm,Promethium",
	"Sm,Samarium",
	"Eu,Europium",
	"Gd,Gadolinium",
	"Tb,Terbium",
	"Dy,Dysprosium",
	"Ho,Holmium",
	"Er,Erbium",
	"Tm,Thulium",
	"Yb,Ytterbium",
	"Lu,Lutetium",
	"Hf,Hafnium",
	"Ta,Tantalum",
	"W,Tungsten",
	"Re,Rhenium",
	"Os,Osmium",
	"Ir,Iridium",
	"Pt,Platinum",
	"Au,Gold",
	"Hg,Mercury",
	"Tl,Thallium",
	"Pb,Lead",
	"Bi,Bismuth",
	"Po,Polonium",
	"At,Astatine",
	"Rn,Radon",
	"Fr,Francium",
	"Ra,Radium",
	"Ac,Actinium",
	"Th,Thorium",
	"Pa,Protactinium",
	"U,Uranium",
	"Np,Neptunium",
	"Pu,Plutonium",
	"Am,Americium",
	"Cm,Curium",
	"Bk,Berkelium",
	"Cf,Californium",
	"Es,Einsteinium",
	"Fm,Fermium",
	"Md,Mendelevium",
	"No,Nobelium",
	"Lr,Lawrencium",
	"Rf,Rutherfordium",
	"Db,Dubnium",
	"Sg,Seaborgium",
	"Bh,Bohrium",
	"Hs,Hassium",
	"Mt,Meitnerium",
	"Ds,Darmstadtium",
	"Rg,Roentgenium",
	"Cn,Copernicium",
	"Nh,Nihonium",
	"Fl,Flerovium",
	"Mc,Moscovium",
	"Lv,Livermorium",
	"Ts,Tennessine",
	"Og,Oganesson"};

int main(void) {
	char op[30];
	char symbol[3], name[30];
	int64_t index;
	while (true) {
		puts("Enter atomic number, name, or symbol (blank to exit):");
		gets(op);
		if (op[0] == '\0') {
			break;
		}
		index = 0;
		if (isalpha(op[0])) {
			if (strlen(op) <= 2) {
				for (size_t i = 0; i != sizeof(elements) / sizeof(elements[0]); ++i) {
					size_t j = strstr(elements[i], ",") - elements[i];
					strncpy(symbol, elements[i], j);
					symbol[j] = '\0';
					if (!strcmp(op, symbol)) {
						index = i + 1;
						break;
					}
				}
				if (index) {
					printf("Atomic number: %" PRId64 "\n", index);
				} else {
					printf("No element found with name or symbol '%s'.\n", op);
					continue;
				}
			} else {
				for (size_t i = 0; i != sizeof(elements) / sizeof(elements[0]); ++i) {
					size_t j = strstr(elements[i], ",") - elements[i];
					strcpy(name, elements[i] + j + 1);
					if (!strcmp(op, name)) {
						index = i + 1;
						break;
					}
				}
				if (index) {
					printf("Atomic number: %" PRId64 "\n", index);
				} else {
					printf("No element found with name or symbol '%s'.\n", op);
					continue;
				}
			}
		} else {
			index = atoi(op) - 1;
			if (0 <= index && index < sizeof(elements) / sizeof(elements[0])) {
				size_t j = strstr(elements[index], ",") - elements[index];
				strncpy(symbol, elements[index], j);
				symbol[j] = '\0';
				printf("Element: %s (Symbol: %s)\n", elements[index] + j + 1, symbol);
			} else {
				printf("No element found with atomic number %" PRId64 ".\n", index + 1);
				continue;
			}
		}
	}
	return 0;
}