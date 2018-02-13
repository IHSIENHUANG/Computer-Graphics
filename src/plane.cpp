
#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    //r(t) = e+ut;
    //u = ray.direction
    //e = ray.endpoint
    //n*p =0
    vec3 e = ray.endpoint;
    vec3 u = ray.direction;
   // if(dot(normal,normal)>1)
     //   printf("wwwwwwwwww");
    if(dot(normal.normalized(),u)==0)
         return false;
    //double t =dot(x1-ray.endpoint,normal)/dot(ray.direction,normal);
    double t = (dot(x1,normal)-dot(e,normal) )/ dot(u,normal);
    Hit new_hit;
    if(t>0)
    {
        Object* obj = new Plane(x1,normal.normalized());
        new_hit.t=t;
        new_hit.object=this;
        new_hit.ray_exiting=true;
        if(dot(ray.direction,normal) <0)//for outside the plane to inside the plane
        {
           
            new_hit.ray_exiting = false;
            hits.push_back(new_hit);
        }
        else
        {
            Hit hit0;
            hit0.object=obj;
            hit0.t=0;
            hit0.ray_exiting=true;
            hits.push_back(hit0);    
            hits.push_back(new_hit);
        }
        return true;
    }
    /*
    else if(t==0)
    {
        new_hit.object=this;
        new_hit.t=t;
        if(dot(ray.direction,normal.normalized())>0)
            new_hit.ray_exiting = true;
        else
            new_hit.ray_exiting = false;
        printf("t =0\n");
        return true;
    }
    */
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}

