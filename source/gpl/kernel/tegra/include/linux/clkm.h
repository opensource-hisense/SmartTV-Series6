

#ifndef __LINUX_CLKM_H
#define __LINUX_CLKM_H


int get_handle(char *name);

int set_clk_source(int handle , char *clk_src_name);

int clk_gate_disable(int handle);


#endif
