#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    //R(t) = e + td //vec3 e,d;endpoint and direction
    //S(X) = (x-c)+(x-c) 
    // a = d*d : double
    // b = 2*d*(e-c) : double
    // c = (e-c) * (e-c) -r*r: double
    // t2 > t1
    double a = dot(ray.direction, ray.direction);
    double b = 2.0* dot((ray.direction), (ray.endpoint - center));
    double c = dot((ray.endpoint - center) , (ray.endpoint - center))-radius*radius;
    double t1,t2;
    double decision = b*b-4.0*a*c;
    Hit new_hit1,new_hit2;
    if(decision < 0)
	 return false;
    else if( decision== 0)
    {
	/*t1= ((-1.0)*(b)+sqrt(decision))/(2.0*a);
        new_hit1.t = t1;
	if(t1<0)
        	new_hit1.ray_exiting= true;
        hits.push_back(new_hit1);*/
	return false; 	
    }
    else
    {
	t1= ((-1.0)*(b)-sqrt(decision))/(2.0*a);

        new_hit1.t = t1;
	new_hit1.ray_exiting = false;
	t2= ((-1.0)*(b)+sqrt(decision))/(2.0*a);
        new_hit1.t = t2;
        new_hit2.ray_exiting = true;
	new_hit1.object=this;
	new_hit2.object=this;
	if(t1>0)//if t1 is exiting it should not be viewed as hit
		hits.push_back(new_hit1);
	if(t2>0)
		hits.push_back(new_hit2);
	return true;
    }   
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    normal = point.normalized();
    return normal;
}
