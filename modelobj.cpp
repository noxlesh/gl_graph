#include "modelobj.h"

ModelObj::ModelObj()
{
    objFile.setFileName("cube.obj");
    #ifdef Q_OS_LINUX
    setlocale(LC_NUMERIC, "C");
    #endif
}

void ModelObj::LoadMdl()
{
    if(!objFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Error loading file
        qDebug("Loading obj model failed");
        return;
    }
    while(!objFile.atEnd()) {
        QByteArray line = objFile.readLine();
        switch(line.at(0))
        {
        case '#':
            //qDebug("Line ignored:found comment");
            break;
        case 'v':
            ParceV(line);
            break;
        case 'f':
            ParceF(line);
            break;
        }
    }
}

vtxArray ModelObj::GetVertices()
{
    //Check for vtxArr consistency
    if(vtxArr.capacity() == 0) {
        qDebug("Vertex array is empty:");
        if(!objFile.isOpen())
            qDebug("Model file not loaded!");
        else
            qDebug("Something goes wrong!");
    }
    return vtxArr;//All goes right
}

faceArray ModelObj::GetFaces()
{
    return fArr;
}

void ModelObj::ParceV(QByteArray line)
{
    vertex tmpVtx;
    sscanf(line.data(),"v %f %f %f",&tmpVtx.x,&tmpVtx.y,&tmpVtx.z);
    vtxArr.push_back(tmpVtx);
}

void ModelObj::ParceF(QByteArray line)
{
    face tmpFace;
    sscanf(line.data(),"f %d %d %d",&tmpFace.x,&tmpFace.y,&tmpFace.z);
    fArr.push_back(tmpFace);
}

