#define __EXTENSIONS__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <zlib.h>
#include "gbfp.h"
 
void help(void) {
        printf("Convert GenBank sequence into FASTA sequence.\n"
        "\n"
        "Usage: seqext [-h] [-V] [-f Feature_to_extract (default: gene)] [-q Qualifier_to_print] [-i Genbank_file]\n"
        "\n"
        "-V  print version information and exit\n");
}

int main(int argc, char *argv[]) {
    char *sFileName = NULL;
    char *sFeature = "gene";
    char *sQualifier = NULL;
    int translate = 0;

    gb_data **pptSeqData, *ptSeqData;
    gb_feature *ptFeature;
    gb_qualifier *ptQualifier;

    unsigned int iOpt;
    unsigned int i, j, k;
    
    if (argc < 2) {
        help();
        exit(0);
    }

    while((iOpt = getopt(argc, argv, "f:i:q:t:h")) != -1) {
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
            translate = atoi(optarg);
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
                        printf(">%s_%li_%li\n", \
                            ptFeature->sFeature, \
                            ptFeature->lStart, \
                            ptFeature->lEnd);
                        if (translate) {
                            char *aaSeq;
                            aaSeq = seqTranslate(getSequence(ptSeqData->sSequence, ptFeature), stdcode1);
                            printf("%s\n", aaSeq);
                            free(aaSeq);
                        } else {
                            printf("%s\n", getSequence(ptSeqData->sSequence, ptFeature));
                        }
                    } else {
                        for (k = 0; k < ptFeature->iQualifierNum; k++) {
                            ptQualifier = (ptFeature->ptQualifier + k);
                            if (strcmp(sQualifier, ptQualifier->sQualifier) == 0) {
                                printf(">%s_%li_%li %s\n", \
                                    ptFeature->sFeature, \
                                    ptFeature->lStart, \
                                    ptFeature->lEnd, \
                                    ptQualifier->sValue);
                                    if (translate) {
                                        char *aaSeq;
                                        aaSeq = seqTranslate(getSequence(ptSeqData->sSequence, ptFeature), stdcode1);
                                        printf("%s\n", aaSeq);
                                        free(aaSeq);
                                    } else {
                                        printf("%s\n", getSequence(ptSeqData->sSequence, ptFeature));
                                    }
                                break;
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
