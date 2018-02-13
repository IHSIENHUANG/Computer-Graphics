#include "boolean.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "hit.h"
#include "shader.h"
#include "render_world.h"
using namespace std;
#define DEBUG 0
// Determine if the ray intersects with the boolean of A and B.
bool cmp(Hit C,Hit D)
{
    return C.t < D.t;    
}

bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    
    vector<Hit> bool_set_A;
    vector<Hit> bool_set_B;
    bool bool_A = A->Intersection(ray,bool_set_A);
    bool bool_B = B->Intersection(ray,bool_set_B);
    int AS = bool_set_A.size();
    int BS = bool_set_B.size();
    if(AS)
        sort(bool_set_A.begin(),bool_set_A.end(),cmp);
    if(BS)
        sort(bool_set_B.begin(),bool_set_B.end(),cmp);
    vector<Hit> union_vec; 
        
    if(type==type_union)//A+B
    {
        if(AS)
        {
            for(int i =0;i<bool_set_A.size();i++)
                hits.push_back(bool_set_A[i]);    
        }
        if(BS)
        {
            for(int i=0;i<bool_set_B.size();i++)
                hits.push_back(bool_set_B[i]);    
        }
    }
    else if(type == type_intersection)//A*B
    {
        if(AS && BS)
        {
            for(int i = 0;i<AS;i++)
            {
                hits.push_back(bool_set_A[i]);    
            }
            for(int j = 0 ; j<BS;j++)
            {
                
                hits.push_back(bool_set_B[j]);    
            }
        }        
    }
    else if(type ==type_difference && bool_A)//A-B
    {
       
        int flag1=1;
        int flag2=1;
    #if DEBUG
        if(AS!=2&& AS!=0)
            cout<<AS<<endl;   
       
    #endif

         
        if(AS && BS)
        {
            Hit tempA1 = bool_set_A[0]; 
            Hit tempA2 = bool_set_A[1];
            if(BS==2)
            {
                Hit tempB1 = bool_set_B[0];
                Hit tempB2 = bool_set_B[1];
                if(tempB1.t>small_t && tempB1.t < tempA1.t && tempB2.t>tempA1.t)
                    flag1= -1;
                if(tempB2.t>small_t && tempB1.t < tempA2.t && flag1!=-1  )
                    flag2 =0;  

            } 
        }
        
        if(flag1==1  && AS  )
            hits.push_back(bool_set_A[0]);
        if(flag2==1 && AS )
            hits.push_back(bool_set_A[1]);
          
        
    }
       
   
 
    if(hits.size()>0)
        return true;
        
    

    return false;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}
