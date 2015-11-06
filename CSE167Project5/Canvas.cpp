//
//  Canvas.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/11/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Canvas.hpp"
Canvas::Canvas(){
    size = width = height = 0;
    pixels = 0;
    rastMode = 0;
    debug =false;
    lsource = LightSource();
}
Canvas::Canvas(int x,int y){
    width = x;
    width = y;
    size = width*height*3;
    pixels = new float[x * y * 3];
    rastMode = 0;
    debug =false;
    lsource = LightSource();

}
void Canvas::update(int x,int y){
    width = x;
    height = y;
    size = width*height*3;
    if(pixels != 0){
        delete pixels;
        delete zbuff;
    }
    pixels =  new float[x*y*3];
    zbuff = new float[x*y];
    lsource = LightSource();
}
float& Canvas::operator [] (int x){
    return pixels[x];
    
}
float * Canvas::getArr(){
    return pixels;
}
void Canvas::rasterVetices(OBJObject * obj,Matrix4 transform,Matrix4& port){
    std::vector<Vector3*>* vert = obj->getVert();
   // std::cout<<width<<" "<<height<<std::endl;
    for(auto it = vert->begin();it!=vert->end();it++){
        Vector4 v4 = Vector4((**it)[0],(**it)[1],(**it)[2],1);
        Vector4 finC = convert(v4, transform, port);
        if(finC[0]<0 ||finC[0]>=width ||finC[1]<0 || finC[1]>=height || finC[2]<0||finC[2]>1){
            continue;
        }
        
        //finC.print("kk ");
        int coord =(int)(((int)finC[1])*((int)width)*3+((int)finC[0])*3);
        //std::cout<<"coor "<<coord<<std::endl;
        //std::cout<<"size "<<size<<std::endl;
        pixels[coord] =1.0;
        pixels[coord+1] = 1.0;
        pixels[coord+2] = 1.0;
    }
    
}
void Canvas::clear(){
    for (int i=0; i<width*height; ++i)
    {
        pixels[i*3]   = 0;
        pixels[i*3+1] = 0;
        pixels[i*3+2] = 0;
        zbuff[i] = 1;
    }
}
Vector4  Canvas::convert(Vector4 &p, Matrix4 &trans, Matrix4 & port){
    Vector4 res;
    res = trans*p;
    res = res.dehomogenize();
    
    res = port*res;
   // res.print("p ");
    return res;
}
static int min(int a ,int b){
    return a<b ? a:b;
}
static int max(int a, int b){
    return a<b ? b:a;
}
/*
 Optimizations TODO?
bool Canvas::testBox(int x0,int y0,int x1,int y1,Vector3 x,Vector3 y){
    for(int i = 0;i<3;i++){
        if((x0<=x[i] && x[i]<x1) && (y0<=y[i] && y[i]<y1)){
            return true;
        }
    }
    getBaryCoordinates(int x0,int y0,int x1,int y1,int x2,int y2,int x,int y)
    
    
}
void Canvas::traverseBox(int x0,int y0,int x1,int y1,int mw,int mh,Vector3 x,Vector3 y){
    int w = x1 -x0;
    int h = y1 -y0;
    if(mh>=h && mw>=w){
        
    }
    int lw = w/2;
    int rw = w-lw;
    int up = h/2;
    int down = h - up;
}*/

void Canvas::rasterTriangles(OBJObject * obj,Vector3 e,Matrix4 tTrans,Matrix4 transform,Matrix4& port){
    
    std::vector<Vector3*>* vert = obj->getVert();
    std::vector<Face*> *faces = obj->faces;
    std::vector<Vector3*> *norms = obj->getNorms();
    
    Vector3 ka =Vector3(.5,.5,.5);
    Vector3 ks = Vector3(200,200,200);
    Vector3 kd = Vector3(20,20,20);
    Vector3 white = Vector3(1,1,1);
    Vector3 lc0 = lsource.coord;
    lsource.coord = (transform*Vector4(lsource.coord[0],lsource.coord[1],lsource.coord[2],1)).toVector3();
    Matrix4 ctrans = transform;
    transform = transform*obj->toWorld;
   // lsource.coord.print("ls");
    //  std::cout<<rastMode<<std::endl;
    
  
 
    for(int i = 0;i<faces->size();i++){

        
        Face * face = faces->at(i);
        int ind0 = face->vertexIndices[0];
        int ind1 = face->vertexIndices[1];
        int ind2 = face->vertexIndices[2];
        Vector4 p1 = Vector4((*((*vert)[ind0]))[0], (*((*vert)[ind0]))[1], (*((*vert)[ind0]))[2],1);
        Vector4 p2 = Vector4((*((*vert)[ind1]))[0], (*((*vert)[ind1]))[1], (*((*vert)[ind1]))[2],1);
        Vector4 p3 = Vector4((*((*vert)[ind2]))[0], (*((*vert)[ind2]))[1], (*((*vert)[ind2]))[2],1);
        Vector4 p0 = p1;
        Vector4 p5 = p2;
        Vector4 p6 = p3;
        
        //EC STUFF
        p1 = transform*p1;
        p2 = transform*p2;
        p3 = transform*p3;
        
        float r = ((double)(rand() % 100 + 1))/100.0;
        float g = ((double)(rand() % 100 + 1))/100.0;
        float b = ((double)(rand() % 100 + 1))/100.0;
        Vector3 v1c = Vector3(r,g,b);
        r = ((double)(rand() % 100 + 1))/100.0;
        g = ((double)(rand() % 100 + 1))/100.0;
        b = ((double)(rand() % 100 + 1))/100.0;
        Vector3 v2c = Vector3(r,g,b);
        r = ((double)(rand() % 100 + 1))/100.0;
        g = ((double)(rand() % 100 + 1))/100.0;
        b = ((double)(rand() % 100 + 1))/100.0;
        Vector3 v3c = Vector3(r,g,b);

        
        Vector3 l0 = lsource.getL(p1.toVector3());
        Vector3 l1 = lsource.getL(p2.toVector3());
        Vector3 l2 = lsource.getL(p3.toVector3());

        Vector3 white = Vector3(1,1,1);
        Vector3 n0 = *(norms->at(face->normalIndices[0]));
        Vector3 n1 = *(norms->at(face->normalIndices[1]));
        Vector3 n2 = *(norms->at(face->normalIndices[2]));

        Vector4 temp = transform*Vector4(n0[0],n0[1],n0[2],0);
        n0 = temp.toVector3();
        temp = transform*Vector4(n1[1],n1[2],n1[3],0);
        n1 = temp.toVector3();
        temp = transform*Vector4(n2[1],n2[2],n2[3],0);
        n2 = temp.toVector3();
        
        Vector3 h0 = (l0+p1.toVector3()).normalize();//lsource.getC(p1.toVector3());
        Vector3 h1 = (l1+p2.toVector3()).normalize();//lsource.getC(p2.toVector3());
        Vector3 h2 = (l2+p3.toVector3()).normalize();//lsource.getC(p3.toVector3());
        
        Vector3 c0 = lsource.getC(p1.toVector3());
        Vector3 c1 = lsource.getC(p2.toVector3());
        Vector3 c2 = lsource.getC(p3.toVector3());
        
        
         
       // p0.print("");
        //p1.print("lll");
      //  transform = projection*transform;
        p1 = convert(p0, tTrans, port);
        p2 = convert(p5, tTrans, port);
        p3 = convert(p6, tTrans, port);
        
    
        


        int bx0 = max(0,min(p3[0],min(p1[0],p2[0])));
        int by0 = max(0,min(p3[1],min(p1[1],p2[1])));
        int bx1 = min(width-1,max(p3[0],max(p1[0],p2[0])));
        int by1 = min(height-1,max(p3[1],max(p1[1],p2[1])));
        // std::cout<<"help \n";
        for(int i = bx0;i<=bx1;i++){
            
            for(int j = by0;j<=by1;j++){
                float mn0 = 0;
                float mn1 = 0;
                float mn2 = 0;
                int coord =(int)(((int)j)*((int)width)*3+((int)i)*3);
                
                Vector3 a = p1.toVector3();
                Vector3 bb = p2.toVector3();
                Vector3 c = p3.toVector3();
                a[2] = bb[2]=c[2] = 0;
                Vector3 p = Vector3(i,j,0);
                // Vector3 baryCoord = getBaryCoordinates(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], i, j);
                Vector3 baryCoord2 =getBaryCoordinates(a, bb, c, p);
                // baryCoord.print("Jjj");
                //baryCoord2.print("Lll");
                if(0<=baryCoord2[0] && baryCoord2[0]<=1 && 0<=baryCoord2[1]
                   && baryCoord2[1]<=1 && 0<=baryCoord2[2] && baryCoord2[2]<=1){
                    
                    float z_pos = p1[2]*(baryCoord2[0])+(p2[2])*baryCoord2[1]+(p3[2])*baryCoord2[2];
                    
                    if(rastMode == 4){
                        mn0 =baryCoord2[0]*n0[0]+baryCoord2[1]*n1[0]+baryCoord2[2]*n2[0];
                        mn1 =baryCoord2[0]*n0[1]+baryCoord2[1]*n1[1]+baryCoord2[2]*n2[1];
                        mn2 =baryCoord2[0]*n0[2]+baryCoord2[1]*n1[2]+baryCoord2[2]*n2[2];
                        
                        Vector3 mnorm = Vector3(mn0,mn1,mn2).normalize();
                        float ml0 = baryCoord2[0]*l0[0]+baryCoord2[1]*l1[0]+baryCoord2[2]*l2[0];
                        float ml1 = baryCoord2[0]*l0[1]+baryCoord2[1]*l1[1]+baryCoord2[2]*l2[1];
                        float ml2 = baryCoord2[0]*l0[2]+baryCoord2[1]*l1[2]+baryCoord2[2]*l2[2];
                        Vector3 ml = Vector3(ml0,ml1,ml2);
                        
                        float mh0 = baryCoord2[0]*h0[0]+baryCoord2[1]*h1[0]+baryCoord2[2]*h2[0];
                        float mh1 = baryCoord2[0]*h0[1]+baryCoord2[1]*h1[1]+baryCoord2[2]*h2[1];
                        float mh2 = baryCoord2[0]*h0[2]+baryCoord2[1]*h1[2]+baryCoord2[2]*h2[2];
                        
                        Vector3 mh = Vector3(mh0,mh1,mh2);
                        
                        float mr =baryCoord2[0]*v1c[0]+baryCoord2[1]*v2c[0]+baryCoord2[2]*v3c[0];
                        float mg =baryCoord2[0]*v1c[1]+baryCoord2[1]*v2c[1]+baryCoord2[2]*v3c[1];
                        float mb =baryCoord2[0]*v1c[2]+baryCoord2[1]*v2c[2]+baryCoord2[2]*v3c[2];
                        Vector3 mc = Vector3(mr,mg,mb);
                        
                        float mc0 =baryCoord2[0]*c0[0]+baryCoord2[1]*c1[0]+baryCoord2[2]*c2[0];
                        float mc1 =baryCoord2[0]*c0[1]+baryCoord2[1]*c1[1]+baryCoord2[2]*c2[1];
                        float mc2 =baryCoord2[0]*c0[2]+baryCoord2[1]*c1[2]+baryCoord2[2]*c2[2];
                        
                        Vector3 myc = Vector3(mc0,mc1,mc2);
                       // myc.print("jj");
                        Vector3 myS= myc*(kd*(ml.dot(mnorm))+ks*pow(mh.dot(mnorm),20))+ka*mc;
                        //myS.print("k");
                        r = myS[0];
                        g = myS[1];
                        b = myS[2];
                        /*
                        r = baryCoord2[0]*v1c[0]+baryCoord2[1]*v2c[0]+baryCoord2[2]*v3c[0];
                        g = baryCoord2[0]*v1c[1]+baryCoord2[1]*v2c[1]+baryCoord2[2]*v3c[1];
                        b = baryCoord2[0]*v1c[2]+baryCoord2[1]*v2c[2]+baryCoord2[2]*v3c[2];
                         */
                        /*
                        r = baryCoord2[0]*n0[0]+baryCoord2[1]*n1[0]+baryCoord2[2]*n2[0];
                        g = baryCoord2[0]*n0[1]+baryCoord2[1]*n1[1]+baryCoord2[2]*n2[1];
                        b = baryCoord2[0]*n0[2]+baryCoord2[1]*n1[2]+baryCoord2[2]*n2[2];*/
                    }
                    bool color = rastMode<=1|| ((zbuff[((int)j)*((int)width)+(int)i]>=z_pos && z_pos>=0));
                    if(zbuff[((int)j)*((int)width)+(int)i]>=z_pos && z_pos>=0 ){
                        zbuff[((int)j)*((int)width)+(int)i] = z_pos;
                        
                    }
                    if (color){
                        if(!(debug && (j == by0 || j==by1||i==bx0 || i == bx1) )){
                            pixels[coord] = r;
                            pixels[coord+1] = g;
                            pixels[coord+2] = b;
                        }
                    }
                    
                }
                if(debug){
                    if(j == by0 || j == by1){
                        pixels[coord] = 1;
                        pixels[coord+1] = 1;
                        pixels[coord+2] = 1;
                    }
                    else if(i==bx0 || i == bx1){
                        pixels[coord] = 1;
                        pixels[coord+1] = 1;
                        pixels[coord+2] = 1;
                    }
                }
                
            }
        }
        
        
    }
    lsource.coord = lc0;
   // lsource.coord.print("done");

  
    
    
}
void Canvas::rasterTriangles(OBJObject * obj,Matrix4 transform,Matrix4& port){
      std::vector<Vector3*>* vert = obj->getVert();
      std::vector<Face*> *faces = obj->faces;
      std::vector<Vector3*> *norms = obj->getNorms();
  //  std::cout<<rastMode<<std::endl;
      for(int i = 0;i<faces->size();i++){
          Face * face = faces->at(i);
          int ind0 = face->vertexIndices[0];
          int ind1 = face->vertexIndices[1];
          int ind2 = face->vertexIndices[2];
          Vector4 p1 = Vector4((*((*vert)[ind0]))[0], (*((*vert)[ind0]))[1], (*((*vert)[ind0]))[2],1);
          Vector4 p2 = Vector4((*((*vert)[ind1]))[0], (*((*vert)[ind1]))[1], (*((*vert)[ind1]))[2],1);
          Vector4 p3 = Vector4((*((*vert)[ind2]))[0], (*((*vert)[ind2]))[1], (*((*vert)[ind2]))[2],1);
          p1 = convert(p1, transform, port);
          p2 = convert(p2, transform, port);
          p3 = convert(p3, transform,port);
          
          
          
          float r = ((double)(rand() % 100 + 1))/100.0;
          float g = ((double)(rand() % 100 + 1))/100.0;
          float b = ((double)(rand() % 100 + 1))/100.0;
          Vector3 n1 = (norms->at(face->normalIndices[0]))->colorize();
          Vector3 n2 = (norms->at(face->normalIndices[1]))->colorize();
          Vector3 n3 = (norms->at(face->normalIndices[2]))->colorize();
          int bx0 = max(0,min(p3[0],min(p1[0],p2[0])));
          int by0 = max(0,min(p3[1],min(p1[1],p2[1])));
          int bx1 = min(width-1,max(p3[0],max(p1[0],p2[0])));
          int by1 = min(height-1,max(p3[1],max(p1[1],p2[1])));
                   // std::cout<<"help \n";
          for(int i = bx0;i<=bx1;i++){
              
              for(int j = by0;j<=by1;j++){
                  int coord =(int)(((int)j)*((int)width)*3+((int)i)*3);
               
                  Vector3 a = p1.toVector3();
                  Vector3 bb = p2.toVector3();
                  Vector3 c = p3.toVector3();
                  a[2] = bb[2]=c[2] = 0;
                  Vector3 p = Vector3(i,j,0);
                 // Vector3 baryCoord = getBaryCoordinates(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], i, j);
                  Vector3 baryCoord2 =getBaryCoordinates(a, bb, c, p);
                 // baryCoord.print("Jjj");
                  //baryCoord2.print("Lll");
                  if(0<=baryCoord2[0] && baryCoord2[0]<=1 && 0<=baryCoord2[1]
                     && baryCoord2[1]<=1 && 0<=baryCoord2[2] && baryCoord2[2]<=1){
                     
                      float z_pos = p1[2]*(baryCoord2[0])+(p2[2])*baryCoord2[1]+(p3[2])*baryCoord2[2];
                   
                      if(rastMode == 3){
                          r = baryCoord2[0]*n1[0]+baryCoord2[1]*n2[0]+baryCoord2[2]*n3[0];
                          g = baryCoord2[0]*n1[1]+baryCoord2[1]*n2[1]+baryCoord2[2]*n3[1];
                          b = baryCoord2[0]*n1[2]+baryCoord2[1]*n2[2]+baryCoord2[2]*n3[2];
                      }
                      bool color = rastMode<=1|| ((zbuff[((int)j)*((int)width)+(int)i]>=z_pos && z_pos>=0));
                      if(zbuff[((int)j)*((int)width)+(int)i]>=z_pos && z_pos>=0 ){
                          zbuff[((int)j)*((int)width)+(int)i] = z_pos;
                       
                      }
                      if (color){
                          if(!(debug && (j == by0 || j==by1||i==bx0 || i == bx1) )){
                        pixels[coord] = r;
                        pixels[coord+1] = g;
                        pixels[coord+2] = b;
                          }
                      }
                
                  }
                  if(debug){
                      if(j == by0 || j == by1){
                          pixels[coord] = 1;
                          pixels[coord+1] = 0;
                          pixels[coord+2] = 0;
                      }
                      else if(i==bx0 || i == bx1){
                          pixels[coord] = 1;
                          pixels[coord+1] = 0;
                          pixels[coord+2] = 0;
                      }
                  }
                  
              }
          }
     
          
      }
}
Vector3 Canvas::getBaryCoordinates(Vector3 a,Vector3 b,Vector3 c,Vector3 p){
    Vector3 e01 = b-a;
    Vector3 e12 = c-b;
    Vector3 e02 = a-c;
    Vector3 n = e01.cross(e12).normalize();
    float area = .5*((e01.cross(e12)).dot(n));
    float au = .5*(e12.cross(p-b).dot(n));
    float av = .5*(e02.cross(p-c).dot(n));
    return Vector3(au/area,av/area,1-au/area-av/area);
}
Vector3 Canvas::getBaryCoordinates(int x1,int y1,int x2,int y2,int x3,int y3,int x,int y){
    float det =(y2-y3)*(x1-x3)+(x3-x2)*(y1-y3);
    float alpha = ((y2-y3)*(x-x3)+(x3-x2)*(y-y3))/det;
    float beta =((y3-y1)*(x-x3)+(x1-x3)*(y-y3))/det;
    float gamma =1-alpha-beta;
    return Vector3(alpha,beta,gamma);
}
