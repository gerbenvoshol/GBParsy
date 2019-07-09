#include "Python.h"
#include "gbfp.h"

static PyObject *ErrorObject;

#define checkString( x ) x != NULL ? x : ""
#define SET_ITEM_STRING( x, y, z ) \
    PyDict_SetItemString(x, y, (Temp = z)); \
    Py_XDECREF(Temp)


PyObject *makeLocationList(gb_location *ptLocation, unsigned int iLocationNum) {
    unsigned int i;
    gb_location *ptLocData;
    PyObject *LocationList;
    PyObject *LocationTuple;

    LocationList = PyList_New(0);

    for (i = 0; i < iLocationNum; i++) {
        ptLocData = ptLocation + i;
        
        LocationTuple = PyTuple_New(2);
        PyTuple_SetItem(LocationTuple, 0, PyInt_FromLong((long) ptLocData->lStart));
        PyTuple_SetItem(LocationTuple, 1, PyInt_FromLong((long) ptLocData->lEnd));
        PyList_Append(LocationList, LocationTuple);
        Py_XDECREF(LocationTuple);
    }

    return LocationList;
}

PyObject *makeQualifierList(gb_qualifier *ptQualifier, unsigned int iQualifierNum) {
    unsigned int i;
    gb_qualifier *ptQualData;
    PyObject *QualifierList;
    PyObject *QualifierTuple;

    QualifierList = PyList_New(0);

    for (i = 0; i < iQualifierNum; i++) {
        ptQualData = ptQualifier + i;

        QualifierTuple = PyTuple_New(2);
        PyTuple_SetItem(QualifierTuple, 0, PyString_FromString(ptQualData->sQualifier));
        PyTuple_SetItem(QualifierTuple, 1, PyString_FromString(ptQualData->sValue));
        PyList_Append(QualifierList, QualifierTuple);
        Py_XDECREF(QualifierTuple);
    }

    return QualifierList;
}

PyObject *makeFeatureDict(gb_feature *ptFeature) {
    PyObject *FeatureDict;
    PyObject *Temp;

    FeatureDict =  PyDict_New();

    /*
    PyDict_SetItemString(FeatureDict, "feature", PyString_FromString((char *) &(ptFeature->sFeature)));
    PyDict_SetItemString(FeatureDict, "direction", PyString_FromStringAndSize((char *) &(ptFeature->cDirection), 1));
    PyDict_SetItemString(FeatureDict, "start", PyInt_FromLong((long) ptFeature->lStart));
    PyDict_SetItemString(FeatureDict, "end", PyInt_FromLong((long) ptFeature->lEnd));
    PyDict_SetItemString(FeatureDict, "number", PyInt_FromLong((long) ptFeature->iNum));
    PyDict_SetItemString(FeatureDict, "location_num", PyInt_FromLong((long) ptFeature->iLocationNum));
    PyDict_SetItemString(FeatureDict, "qualifier_num", PyInt_FromLong((long) ptFeature->iQualifierNum));
    PyDict_SetItemString(FeatureDict, "locations", makeLocationList(ptFeature->ptLocation, ptFeature->iLocationNum));
    PyDict_SetItemString(FeatureDict, "qualifiers", makeQualifierList(ptFeature->ptQualifier, ptFeature->iQualifierNum));
    */

    SET_ITEM_STRING(FeatureDict, "feature", PyString_FromString((char *) &(ptFeature->sFeature)));
    SET_ITEM_STRING(FeatureDict, "direction", PyString_FromStringAndSize((char *) &(ptFeature->cDirection), 1));
    SET_ITEM_STRING(FeatureDict, "start", PyInt_FromLong((long) ptFeature->lStart));
    SET_ITEM_STRING(FeatureDict, "end", PyInt_FromLong((long) ptFeature->lEnd));
    SET_ITEM_STRING(FeatureDict, "number", PyInt_FromLong((long) ptFeature->iNum));
    SET_ITEM_STRING(FeatureDict, "location_num", PyInt_FromLong((long) ptFeature->iLocationNum));
    SET_ITEM_STRING(FeatureDict, "qualifier_num", PyInt_FromLong((long) ptFeature->iQualifierNum));
    SET_ITEM_STRING(FeatureDict, "locations", makeLocationList(ptFeature->ptLocation, ptFeature->iLocationNum));
    SET_ITEM_STRING(FeatureDict, "qualifiers", makeQualifierList(ptFeature->ptQualifier, ptFeature->iQualifierNum));

    return FeatureDict; 
}

PyObject *makeReferenceDict(gb_reference *ptReference) {
    PyObject *ReferenceDict;
    PyObject *Temp;

    ReferenceDict =  PyDict_New();

    /*
    PyDict_SetItemString(ReferenceDict, "authors", PyString_FromString(checkString(ptReference->sAuthors)));
    PyDict_SetItemString(ReferenceDict, "consrtm", PyString_FromString(checkString(ptReference->sConsrtm)));
    PyDict_SetItemString(ReferenceDict, "title", PyString_FromString(checkString(ptReference->sTitle)));
    PyDict_SetItemString(ReferenceDict, "journal", PyString_FromString(checkString(ptReference->sJournal)));
    PyDict_SetItemString(ReferenceDict, "medline", PyString_FromString(checkString(ptReference->sMedline)));
    PyDict_SetItemString(ReferenceDict, "pubmed", PyString_FromString(checkString(ptReference->sPubMed)));
    PyDict_SetItemString(ReferenceDict, "remark", PyString_FromString(checkString(ptReference->sRemark)));
    PyDict_SetItemString(ReferenceDict, "number", PyInt_FromLong((long) ptReference->iNum));
    */

    SET_ITEM_STRING(ReferenceDict, "authors", PyString_FromString(checkString(ptReference->sAuthors)));
    SET_ITEM_STRING(ReferenceDict, "consrtm", PyString_FromString(checkString(ptReference->sConsrtm)));
    SET_ITEM_STRING(ReferenceDict, "title", PyString_FromString(checkString(ptReference->sTitle)));
    SET_ITEM_STRING(ReferenceDict, "journal", PyString_FromString(checkString(ptReference->sJournal)));
    SET_ITEM_STRING(ReferenceDict, "medline", PyString_FromString(checkString(ptReference->sMedline)));
    SET_ITEM_STRING(ReferenceDict, "pubmed", PyString_FromString(checkString(ptReference->sPubMed)));
    SET_ITEM_STRING(ReferenceDict, "remark", PyString_FromString(checkString(ptReference->sRemark)));
    SET_ITEM_STRING(ReferenceDict, "number", PyInt_FromLong((long) ptReference->iNum));

    return ReferenceDict; 
}

PyObject *makeGBFFDataDict(gb_data *ptGBFFData) {
    int i;

    PyObject *GBFFDataDict;
    PyObject *FeatureList;
    PyObject *ReferenceList;
    PyObject *RegionTuple;
    PyObject *Temp;

    GBFFDataDict =  PyDict_New();

    /*
    PyDict_SetItemString(GBFFDataDict, "locus_name", PyString_FromString((char *) &(ptGBFFData->sLocusName)));
    PyDict_SetItemString(GBFFDataDict, "length", PyInt_FromLong((long) ptGBFFData->lLength));
    PyDict_SetItemString(GBFFDataDict, "type", PyString_FromString((char *) &(ptGBFFData->sType)));
    PyDict_SetItemString(GBFFDataDict, "topology", PyString_FromString((char *) &(ptGBFFData->sTopology)));
    PyDict_SetItemString(GBFFDataDict, "division_code", PyString_FromString((char *) &(ptGBFFData->sDivisionCode)));
    PyDict_SetItemString(GBFFDataDict, "date", PyString_FromString((char *) &(ptGBFFData->sDate)));
    PyDict_SetItemString(GBFFDataDict, "feature_num", PyInt_FromLong((long) ptGBFFData->iFeatureNum));
    PyDict_SetItemString(GBFFDataDict, "sequence", PyString_FromString(checkString(ptGBFFData->sSequence)));
    PyDict_SetItemString(GBFFDataDict, "accession", PyString_FromString(checkString(ptGBFFData->sAccession)));
    PyDict_SetItemString(GBFFDataDict, "comment", PyString_FromString(checkString(ptGBFFData->sComment)));
    PyDict_SetItemString(GBFFDataDict, "definition", PyString_FromString(checkString(ptGBFFData->sDef)));
    PyDict_SetItemString(GBFFDataDict, "gi", PyString_FromString(checkString(ptGBFFData->sGI)));
    PyDict_SetItemString(GBFFDataDict, "keywords", PyString_FromString(checkString(ptGBFFData->sKeywords)));
    PyDict_SetItemString(GBFFDataDict, "lineage", PyString_FromString(checkString(ptGBFFData->sLineage)));
    PyDict_SetItemString(GBFFDataDict, "organism", PyString_FromString(checkString(ptGBFFData->sOrganism)));
    PyDict_SetItemString(GBFFDataDict, "source", PyString_FromString(checkString(ptGBFFData->sSource)));
    PyDict_SetItemString(GBFFDataDict, "version", PyString_FromString(checkString(ptGBFFData->sVersion)));
    */

    SET_ITEM_STRING(GBFFDataDict, "locus_name", PyString_FromString((char *) &(ptGBFFData->sLocusName)));
    SET_ITEM_STRING(GBFFDataDict, "length", PyInt_FromLong((long) ptGBFFData->lLength));
    SET_ITEM_STRING(GBFFDataDict, "type", PyString_FromString((char *) &(ptGBFFData->sType)));
    SET_ITEM_STRING(GBFFDataDict, "topology", PyString_FromString((char *) &(ptGBFFData->sTopology)));
    SET_ITEM_STRING(GBFFDataDict, "division_code", PyString_FromString((char *) &(ptGBFFData->sDivisionCode)));
    SET_ITEM_STRING(GBFFDataDict, "date", PyString_FromString((char *) &(ptGBFFData->sDate)));
    SET_ITEM_STRING(GBFFDataDict, "feature_num", PyInt_FromLong((long) ptGBFFData->iFeatureNum));
    SET_ITEM_STRING(GBFFDataDict, "sequence", PyString_FromString(checkString(ptGBFFData->sSequence)));
    SET_ITEM_STRING(GBFFDataDict, "accession", PyString_FromString(checkString(ptGBFFData->sAccession)));
    SET_ITEM_STRING(GBFFDataDict, "comment", PyString_FromString(checkString(ptGBFFData->sComment)));
    SET_ITEM_STRING(GBFFDataDict, "definition", PyString_FromString(checkString(ptGBFFData->sDef)));
    SET_ITEM_STRING(GBFFDataDict, "gi", PyString_FromString(checkString(ptGBFFData->sGI)));
    SET_ITEM_STRING(GBFFDataDict, "keywords", PyString_FromString(checkString(ptGBFFData->sKeywords)));
    SET_ITEM_STRING(GBFFDataDict, "lineage", PyString_FromString(checkString(ptGBFFData->sLineage)));
    SET_ITEM_STRING(GBFFDataDict, "organism", PyString_FromString(checkString(ptGBFFData->sOrganism)));
    SET_ITEM_STRING(GBFFDataDict, "source", PyString_FromString(checkString(ptGBFFData->sSource)));
    SET_ITEM_STRING(GBFFDataDict, "version", PyString_FromString(checkString(ptGBFFData->sVersion)));

    /* Create list of region */
    RegionTuple = PyTuple_New(2);

    PyTuple_SetItem(RegionTuple, 0, PyInt_FromLong((long) ptGBFFData->lRegion[0]));
    PyTuple_SetItem(RegionTuple, 1, PyInt_FromLong((long) ptGBFFData->lRegion[1]));

    /*
    PyDict_SetItemString(GBFFDataDict, "region", RegionTuple);
    */
    SET_ITEM_STRING(GBFFDataDict, "region", RegionTuple);


    /* Create list of references */
    ReferenceList = PyList_New(0);

    for(i = 0; i < ptGBFFData->iReferenceNum; i++) {
        PyList_Append(ReferenceList, (Temp = makeReferenceDict((ptGBFFData->ptReferences) + i)));
        Py_XDECREF(Temp);
    }

    /*
    PyDict_SetItemString(GBFFDataDict, "references", ReferenceList);
    */
    SET_ITEM_STRING(GBFFDataDict, "references", ReferenceList);

    /* Create list of features */
    FeatureList = PyList_New(0);

    for(i = 0; i < ptGBFFData->iFeatureNum; i++) {
        PyList_Append(FeatureList, (Temp = makeFeatureDict((ptGBFFData->ptFeatures) + i)));
        Py_XDECREF(Temp);
    }

    /*
    PyDict_SetItemString(GBFFDataDict, "features", FeatureList);
    */
    SET_ITEM_STRING(GBFFDataDict, "features", FeatureList);

    return GBFFDataDict;
}

static PyObject *parse(PyObject *self, PyObject *args) {
    int i;
    char *psFileName;

    gb_data **pptGBFFData;

    PyObject *GBFFDataList;
    PyObject *Temp;

    /* Parsing arguments */
    if (!PyArg_ParseTuple(args, "s", &psFileName)) return NULL;
    
    /* Parsing with C function */
    if (strcmp(psFileName, "stdin") == 0) pptGBFFData = parseGBFF(NULL);
    else pptGBFFData = parseGBFF(psFileName);

    if (pptGBFFData != NULL) {
        /* Convert datas from C to Python */
        GBFFDataList = PyList_New(0);

        for (i = 0; *(pptGBFFData + i) != NULL; i++) {
            PyList_Append(GBFFDataList, (Temp = makeGBFFDataDict(*(pptGBFFData + i))));
            Py_XDECREF(Temp);
        }

        freeGBData(pptGBFFData);
        
        return GBFFDataList;
    } else {
        PyErr_SetString(PyExc_IOError, "File not found.");

        return NULL;
    }
}         

static struct PyMethodDef gbfpy_methods[] = { 
    {"parse", parse, METH_VARARGS},
    {NULL, NULL}
};

void initgbfpy(void) {
    PyObject *parser; 
    parser = Py_InitModule("gbfpy", gbfpy_methods);
    ErrorObject = Py_BuildValue("s", "GBFF parser error !!!");
} 
