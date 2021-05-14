#define __EXTENSIONS__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <zlib.h>
#include <ctype.h>

#include "gbfp.h"
 
void help(void) {
        printf("Convert GenBank sequence into FASTA sequence.\n"
        "\n"
        "Usage: seqext [-h] [-V] [-f Feature_to_extract (default: gene)] [-q Qualifier_to_print] [-i Genbank_file]\n"
        "\n"
        "-o  omit the use of location based identifiers (e.g. CDS_995899_996610)\n"
        "-t  translate the extracted DNA sequence\n"
        "-u  convert sequence to upper case\n"
        "-h  print help information and exit\n"
        "-V  print version information and exit\n");
}

char* strupr(char* s)
{
    char* tmp = s;

    for (;*tmp;++tmp) {
        *tmp = toupper((unsigned char) *tmp);
    }

    return s;
}

int main(int argc, char *argv[]) {
    char *sFileName = NULL;
    char *sFeature = "gene";
    char *sQualifier = NULL;
    int translate = 0;
    int omit_id = 0;
    int upper = 0;
    gb_data **pptSeqData, *ptSeqData;
    gb_feature *ptFeature;
    gb_qualifier *ptQualifier;

    unsigned int iOpt;
    unsigned int i, j, k;
    
    if (argc < 2) {
        help();
        exit(0);
    }

    while((iOpt = getopt(argc, argv, "f:i:q:thVou")) != -1) {
        switch(iOpt) {
        case 'h':
            help();
            exit(0);
            break;
        case 'i':
            sFileName = optarg;
            break;
        case 'f':
            sFeature = optarg;
            break;
        case 'q':
            sQualifier = optarg;
            break;
        case 't':
            translate = 1;
            break;
        case 'o':
            omit_id = 1;
            break;
        case 'u':
            upper = 1;
            break;
        default:
            help();
            exit(0);
        }
    }
 
    //fprintf(stderr, "Parsing: %s...", sFileName);
    pptSeqData = parseGBFF(sFileName);
    //fprintf(stderr, "done\n");
    if (pptSeqData != NULL) {
        for (i = 0; (ptSeqData = *(pptSeqData + i)) != NULL; i++) {
            /* printf("%s\n", (ptSeqData->ptReferences)->sAuthors); */
            for (j = 0; j < ptSeqData->iFeatureNum; j++) {
                ptFeature = (ptSeqData->ptFeatures + j);
                if (strcmp(sFeature, ptFeature->sFeature) == 0) {
                    if (sQualifier == NULL) {
                        if (omit_id) {
                            printf(">\n");
                        } else {
                            printf(">%s_%li_%li\n", ptFeature->sFeature, ptFeature->lStart, ptFeature->lEnd);
                        }
                        if (translate) {
                            char *aaSeq;
                            aaSeq = seqTranslate(getSequence(ptSeqData->sSequence, ptFeature), stdcode1);
                            printf("%s\n", aaSeq);
                            free(aaSeq);
                        } else {
                            if (upper) {
                                printf("%s\n", strupr(getSequence(ptSeqData->sSequence, ptFeature)));
                            } else {
                                printf("%s\n", getSequence(ptSeqData->sSequence, ptFeature));
                            }
                        }
                    } else {
                        if (omit_id) {
                            printf(">");
                        } else {
                            printf(">%s_%li_%li ", ptFeature->sFeature, ptFeature->lStart, ptFeature->lEnd);
                        }
                        for (k = 0; k < ptFeature->iQualifierNum; k++) {
                            ptQualifier = (ptFeature->ptQualifier + k);
                            if (strstr(sQualifier, ptQualifier->sQualifier) != 0) {
                                printf("%s ", ptQualifier->sValue);
                                //break;
                            }
                        }
                        printf("\n");
                        if (translate) {
                            char *aaSeq;
                            aaSeq = seqTranslate(getSequence(ptSeqData->sSequence, ptFeature), stdcode1);
                            printf("%s\n", aaSeq);
                            free(aaSeq);
                        } else {
                            if (upper) {
                                printf("%s\n", strupr(getSequence(ptSeqData->sSequence, ptFeature)));
                            } else {
                                printf("%s\n", getSequence(ptSeqData->sSequence, ptFeature));
                            }
                        }
                    }
                }
            }
        }
        freeGBData(pptSeqData);
    }

    return 0;
}
