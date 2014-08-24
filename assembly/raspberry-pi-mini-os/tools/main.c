#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int base_vir = 0xF2000000;
static int base_per = 0x7E000000;
static int base_phy = 0x20000000;

unsigned int phy_to_per(unsigned int addr) {
  unsigned int diff;

  diff = addr - base_phy;
  return base_per + diff;
}

unsigned int per_to_phy(unsigned int addr) {
  unsigned int diff;

  diff = addr - base_per;
  return base_phy + diff;
}

unsigned int phy_to_virt(unsigned int addr) {
  unsigned int diff;

  diff = addr - base_phy;
  return base_vir + diff;
}

unsigned int virt_to_phy(unsigned int addr) {
  unsigned int diff;

  diff = addr - base_vir;
  return base_phy + diff;
}

unsigned int per_to_virt(unsigned int addr) {
  unsigned int diff;

  diff = addr - base_per;
  return base_vir + diff;
}

unsigned int virt_to_per(unsigned int addr) {
  unsigned int diff;

  diff = addr - base_vir;
  return base_per + diff;
}

unsigned int strtohex(const char* hex_str) {
  int i;
  unsigned int val;
  unsigned int len;
  unsigned int pow16;
  unsigned int pow;

  val = 0;
  len = strlen(hex_str);
  pow16 = 0;

  for (i = len - 1; i >= 0; --i, ++pow16) {
    const char tok = hex_str[i];

    pow = 1u << (pow16 * 4);

    if (tok >= '0' && tok <= '9') {
      val += (tok - '0') * pow;
    } else if (tok >= 'A' && tok <= 'F') {
      val += (10u + (tok - 'A')) * pow;
    } else if (i == 1 && (tok == 'x' || tok == 'X')) {
      if (hex_str[0] == '0' && len > 2) {
        break;
      } else {
        val = 0;
        break;
      }
    } else {
      val = 0;
      break;
    }
  }

  return val;
}

int main(int argc, char *argv[]) {
  int status_code;
  unsigned int addr;
  unsigned int calc_addr;
  char *info = NULL;

  status_code = -1;
  addr = 0;
  calc_addr = addr;

  if (argc == 3) {
    addr = strtohex(argv[2]);

    if (addr != 0) {
      status_code = 0;
      if (strcmp(argv[1], "-phy_per") == 0) {
        calc_addr = phy_to_per(addr);
        info = "Peripheral address is ";
      } else if (strcmp(argv[1], "-per_phy") == 0) {
        calc_addr = per_to_phy(addr);
        info = "Physical address is ";
      } else if (strcmp(argv[1], "-phy_virt") == 0) {
        calc_addr = phy_to_virt(addr);
        info = "Virtual address is ";
      } else if (strcmp(argv[1], "-virt_phy") == 0) {
        calc_addr = virt_to_phy(addr);
        info = "Physical address is ";
      } else if (strcmp(argv[1], "-virt_per") == 0) {
        calc_addr = virt_to_per(addr);
        info = "Peripheral address is ";
      } else if (strcmp(argv[1], "-per_virt") == 0) {
        calc_addr = per_to_virt(addr);
        info = "Virtual address is ";
      } else {
        printf("Invalid option %s\n", argv[1]);
        status_code = -1;
      }
    } else {
      printf("Invalid address %s\n", argv[2]);
      status_code = -1;
    }
  } else if(argc == 2 &&
    (strcmp("--help", argv[1]) == 0 || strcmp("-h", argv[1]) == 0)) {

    printf("The options are: [%s | %s | %s | %s | %s | %s] addr\n",
      "-phy_per", "-per_phy", "-phy_virt", "-virt_phy", "-virt_per",
      "-per_virt");
  } else {
    printf("Invalid number of args %d\n", argc);
    status_code = -1;
  }

  if (status_code != -1) {
    printf("%s%x\n", info, calc_addr);
  }

  return status_code;
}
