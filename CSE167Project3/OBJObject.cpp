#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)

OBJObject::OBJObject(){
    
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    
    this->colors = new std::vector<Vector3*>();
    this->toWorld.identity();
    
    spinDir = 1;

}
OBJObject::OBJObject(std::string filename) : Drawable()
{
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    
    this->colors = new std::vector<Vector3*>();
    this->toWorld.identity();
    parse(filename);
    spinDir = 1;
   

}
OBJObject::OBJObject(OBJObject * copy):Drawable(){
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    this->colors = new std::vector<Vector3*>();
    for(auto iter = copy->vertices->begin();iter!=copy->vertices->end();iter++){
        this->vertices->push_back(new Vector3( (**iter)[0],(**iter)[1],(**iter)[2] ) );
    }
    for(auto iter = copy->normals->begin();iter!=copy->normals->end();iter++){
        this->normals->push_back(new Vector3( (**iter)[0],(**iter)[1],(**iter)[2] ) );
    }
    for(auto iter = copy->colors->begin();iter!=copy->colors->end();iter++){
        this->colors->push_back(new Vector3( (**iter)[0],(**iter)[1],(**iter)[2] ) );
    }
    for(auto iter = copy->faces->begin();iter!=copy->faces->end();iter++){
        Face * face = new Face;
        for(int i = 0;i<3;i++){
        face->normalIndices[i] = (*iter)->normalIndices[i];
        face->vertexIndices[i] =(*iter)->vertexIndices[i];
        face->textureIndices[i] = (*iter)->textureIndices[i];
        }
        this->faces->push_back(face );
    }
    spinDir = 1;//copy->spinDir;
    this->toWorld.identity();
}
OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    if(vertices !=0){
        deleteVector(Vector3*, vertices);}
    if(normals!=0){
    deleteVector(Vector3*, normals);
    }
    if(faces!=0){
    deleteVector(Face*, faces);
    }
    if(colors!=0){
    deleteVector(Vector3*,colors);
    }
}

void OBJObject::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glNorm(normals->at(face.normalIndices[0]))
    //      glVert(vertices->at(face.vertexIndices[0]))
    //      Etc.
    //
    //std::cout<<"face "<<faces->size()<<std::endl;

    Face* face;
    unsigned long size =faces->size();
    for(int i = 0; i<size;i++){
        face = faces->at(i);
        
        Vector3 vnorm = *normals->at(face->normalIndices[0]);
        
        glNormal3f(vnorm[0],vnorm[1],vnorm[2]);
        
        
            
        if(colors!= 0 && (face->vertexIndices[0])<colors->size()){
            Vector3 cvert = *colors->at(face->vertexIndices[0]);
            glColor4f(cvert[0],cvert[1],cvert[2],0.5);
        }else{
            glColor4f(1,1,1,0.5);
        }
        Vector3 vvert = *vertices->at(face->vertexIndices[0]);
        glVertex3f(vvert[0],vvert[1],vvert[2]);
        
        vnorm = *normals->at(face->normalIndices[1]);
        
        glNormal3f(vnorm[0],vnorm[1],vnorm[2]);
        
        
        
        if(colors!= 0 && (face->vertexIndices[1])<colors->size()){
            Vector3 cvert = *colors->at(face->vertexIndices[1]);
            glColor4f(cvert[0],cvert[1],cvert[2],0.5);
        }else{
            glColor4f(1,1,1,0.5);
        }
        vvert = *vertices->at(face->vertexIndices[1]);
        glVertex3f(vvert[0],vvert[1],vvert[2]);
        
        vnorm = *normals->at(face->normalIndices[2]);
        
        glNormal3f(vnorm[0],vnorm[1],vnorm[2]);
        
        
        
        if(colors!= 0 && (face->vertexIndices[2])<colors->size()){
            Vector3 cvert = *colors->at(face->vertexIndices[2]);
            glColor4f(cvert[0],cvert[1],cvert[2],0.5);
        }else{
            glColor4f(1,1,1,0.5);
        }
        vvert = *vertices->at(face->vertexIndices[2]);
        glVertex3f(vvert[0],vvert[1],vvert[2]);
        
        
        
    }
    glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        
        //Progress
       // if(++lineNum % 10000 == 0)
         //   std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
       // std::cout<<"LLLLL\n";
        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("v") == 0)
        {
            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            
            vertices->push_back(new Vector3(x, y, z));
  
            if(tokens.size()>4){
          
                colors->push_back(new Vector3(std::stof(tokens.at(4)),std::stof(tokens.at(5)),std::stof(tokens.at(6))));
            }
            
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            Vector3 * vect =  new Vector3(std::stof(tokens.at(1)),std::stof(tokens.at(2)),std::stof(tokens.at(3)));
            vect->normalizeThis();
            normals->push_back(vect);
            
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            
            Face * obj_face = new Face;
            
            //Parse the face line
            
            std::vector<std::string> i0;
            std::vector<std::string> i1;
            std::vector<std::string> i2;
            std::vector<std::vector<std::string>> index;

            i0 = split(tokens.at(1), '/', i0);
            i1 = split(tokens.at(2), '/', i1);
            i2 = split(tokens.at(3), '/', i2);
            
            
            index.push_back(i0);
            index.push_back(i1);
            index.push_back(i2);
            
            
            
            for (int i = 0; i < 3; i++) {
                obj_face->vertexIndices[i] = std::stof(index[i].at(0))-1;
                obj_face->textureIndices[i] = std::stof(index[i].at(0))-1;
                obj_face->normalIndices[i] = std::stof(index[i].at(2))-1;
            }
            
            index.clear();
            
            faces->push_back(obj_face);
            
        }
        else if(tokens.at(0).compare("How does I are C++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
        
    }
    
    std::cout << "Done parsing." << std::endl;

    
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
void OBJObject::toggleSpin(){
    spinDir *= -1;
}
void OBJObject::spin(float rads){
    Matrix4 rotation;
    rotation.makeRotateY(rads*spinDir);
    
    toWorld = toWorld * rotation;
    
}
void OBJObject::trans(float x, float y, float z){
    Matrix4 trans;
    trans.makeTranslate(x, y, z);
    toWorld = trans*toWorld;
}
void OBJObject::reset(){
    toWorld.identity();
    spinDir = 1;
}
void OBJObject::rotate(float scale){
    
    Matrix4 rot;
    rot.makeRotateZ(.10*scale);
    toWorld = rot*toWorld;
    
}
void OBJObject::scale(float sFactor){
    Matrix4 scaly;
    scaly.makeScale(sFactor);
    toWorld = toWorld*scaly;
}
void OBJObject::printCoord(){
    toWorld.printCol(3);
    
}
std::vector<Vector3*>* OBJObject::getVert(){
    return vertices;
}
std::vector<Vector3*> *OBJObject::getNorms(){
    return normals;
}