/*
 * Copyright © 2014 Kosma Moczek <kosma@cloudyourcar.com>
 * This program is free software. It comes without any warranty, to the extent
 * permitted by applicable law. You can redistribute it and/or modify it under
 * the terms of the Do What The Fuck You Want To Public License, Version 2, as
 * published by Sam Hocevar. See the COPYING file for more details.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "minmea.h"

typedef unsigned char UCHAR;

void get_rmc(char *line, char *ret_line)
{
	struct minmea_sentence_rmc frame;
	
	if (minmea_parse_rmc(&frame, line)) 
	{
		sprintf(ret_line, "%f, %f, %f",
		minmea_tocoord(&frame.latitude),
		minmea_tocoord(&frame.longitude),
		minmea_tofloat(&frame.speed));
	}
	return;
}

int get_rmc_frame(char *line, struct minmea_sentence_rmc *frame)
{
	if (minmea_parse_rmc(frame, line))
		return 1;
    return -1;
}

int get_gga_frame(char *line, struct minmea_sentence_gga *frame)
{
	if (minmea_parse_gga(frame, line))
	    return 1;
    return -1;
}

int get_gsa_frame(char *line, struct minmea_sentence_gsa *frame)
{
	if (minmea_parse_gsa(frame, line))
	    return 1;
    return -1;
}

int get_gst_frame(char *line, struct minmea_sentence_gst *frame)
{
	if (minmea_parse_gst(frame, line))
	    return 1;
    return -1;
}

int get_gsv_frame(char *line, struct minmea_sentence_gsv *frame)
{
	if (minmea_parse_gsv(frame, line))
	    return 1;
    return -1;
}

int get_gll_frame(char *line, struct minmea_sentence_gll *frame)
{
	if (minmea_parse_gll(frame, line))
	    return 1;
    return -1;
}

int get_vtg_frame(char *line, struct minmea_sentence_vtg *frame)
{
	if (minmea_parse_vtg(frame, line))
	    return 1;
    return -1;
}

int get_zda_frame(char *line, struct minmea_sentence_zda *frame)
{
	if (minmea_parse_zda(frame, line))
	    return 1;
    return -1;
}

#if 0
int GPS(char *line, void **vstruct)
{
	int i; 
	int ret_val = -1;
	int id = -1;

    UCHAR temp[200];

//	printf("%s\n",line);
//	strcat(line,"\r\n");
	switch (id = minmea_sentence_id(line, false)) 
	{
		case MINMEA_SENTENCE_RMC: 
		{
			struct minmea_sentence_rmc *rmc_frame;
			rmc_frame = (struct minmea_sentence_rmc*)temp;
			if (minmea_parse_rmc(rmc_frame, line)) 
			{
				*vstruct = (void *)rmc_frame;
				ret_val = MINMEA_SENTENCE_RMC;
			}
			else 
			{
				printf("$xxRMC sentence is not parsed\r\n");
			}
		} 
		break;

		case MINMEA_SENTENCE_GGA:
		{
			struct minmea_sentence_gga *gga_frame;
			gga_frame = (struct minmea_sentence_gga*)temp;
			if (minmea_parse_gga(gga_frame, line)) 
			{
//				printf("$xxGGA: fix quality: %d\r\n", frame.fix_quality);
//                printf("c %04x\n",vstruct);
				*vstruct = (void *)gga_frame;
 //               printf("d %04x\n",vstruct);
				ret_val = MINMEA_SENTENCE_GGA;
			}
			else 
			{
				printf("$xxGGA sentence is not parsed\r\n");
			}
		} 
		break;

		case MINMEA_SENTENCE_GSA:
			{
			struct minmea_sentence_gsa *gsa_frame;
			gsa_frame = (struct minmea_sentence_gsa*)temp;
			if (minmea_parse_gsa(gsa_frame, line)) 
			{
				*vstruct = (void *)gsa_frame;
				ret_val = MINMEA_SENTENCE_GSA;
			}
			else 
			{
				printf("$xxGST sentence is not parsed\r\n");
			}
		} 
		break;

		case MINMEA_SENTENCE_GST: 
		{
			struct minmea_sentence_gst *gst_frame;
			gst_frame = (struct minmea_sentence_gst*)temp;
			if (minmea_parse_gst(gst_frame, line)) 
			{
				*vstruct = (void *)gst_frame;
				ret_val = MINMEA_SENTENCE_GST;
			}
			else 
			{
				printf("$xxGST sentence is not parsed\r\n");
			}
		} 
		break;

		case MINMEA_SENTENCE_GSV: 
		{
			struct minmea_sentence_gsv *gsv_frame;
			gsv_frame = (struct minmea_sentence_gsv*)temp;
			if (minmea_parse_gsv(gsv_frame, line)) 
			{
				*vstruct = (void *)gsv_frame;
				ret_val = MINMEA_SENTENCE_GSV;
			}
			else 
			{
				printf("$xxGSV sentence is not parsed\r\n");
			}
		} 
		break;

		case MINMEA_SENTENCE_VTG:
		{
			struct minmea_sentence_vtg *vtg_frame;
			vtg_frame = (struct minmea_sentence_vtg*)temp;
			if (minmea_parse_vtg(vtg_frame, line)) 
			{
				*vstruct = (void *)vtg_frame;
				ret_val = MINMEA_SENTENCE_VTG;
			}
			else 
			{
				printf("$xxVTG sentence is not parsed\r\n");
			}
		} 
		break;

		case MINMEA_SENTENCE_ZDA: 
		{
			struct minmea_sentence_zda *zda_frame;
			zda_frame = (struct minmea_sentence_zda*)temp;
			if (minmea_parse_zda(zda_frame, line)) 
			{
				*vstruct = (void *)zda_frame;
				ret_val = MINMEA_SENTENCE_ZDA;
			}
			else 
			{
			printf("$xxZDA sentence is not parsed\r\n");
			}
		} 
		break;
		
		case MINMEA_SENTENCE_GLL:

		{
			struct minmea_sentence_gll *gll_frame;
			gll_frame = (struct minmea_sentence_gll*)temp;
			if (minmea_parse_gll(gll_frame, line))
			{
				//printf("GLL\n");
				*vstruct = (void *)gll_frame;
        		ret_val = MINMEA_SENTENCE_GLL;
			}
		}
		break;

		case MINMEA_INVALID:
		{
//			printf("INVALID sentence is not valid\r\n");
			ret_val = MINMEA_INVALID;
		} 
		break;

		default: 
		{
//			printf("default sentence is not parsed\r\n");
			ret_val = MINMEA_INVALID;
		} 
		break;
	}	// end of switch
//	printf("sentence id: %d\n",id);
	return ret_val;
}
#endif
/* vim: set ts=4 sw=4 et: */
