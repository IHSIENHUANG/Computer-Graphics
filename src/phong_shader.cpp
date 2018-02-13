#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
using namespace std;
vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
//    printf("this is from phoney");
    vec3 color;
    color = color_ambient*world.ambient_color * world.ambient_intensity;
    // I* N = cos 
    vec3 I;
    vec3 diff_color;
    vec3 R;
    for(unsigned int i =0;i<world.lights.size();i++)
    {


         I = world.lights[i]->position-intersection_point;
    //double diffu = dot(I,same_side_normal);//cos
    //diffu = std::max(0.0,dot(I,same_side_normal);
    
    //shadows

        if(world.enable_shadows)//make sure shadows should be calculated
        {
            // closest intersection make sure there is not block between light and intersection

           const Ray new_ray(intersection_point,I.normalized());

            Hit hit2;
            Object * obj = world.Closest_Intersection(new_ray,hit2);
            //Object * obj;
            vec3 hit_obj = intersection_point + ray.direction*(hit2.t);
            //if obj is behind the light, it will not be count
            double Light_distance = (world.lights[i]->position-intersection_point).magnitude();
            double obj_distance =(hit_obj-intersection_point).magnitude();
            // if there is an object between light and intersection -> return ambient color
            if(obj!=NULL && Light_distance > obj_distance )
            {
                //cout<<obj_distance <<endl;
                continue; 
            }
        }

    //diffuse
        diff_color = world.lights[i]->Emitted_Light(ray);//return color by color * brightness = I ;
        color += color_diffuse*(diff_color *std::max(0.0,dot(I.normalized(),same_side_normal)))/dot(I,I); 

    //specular R = 2*(LN)*N-L
    // specular intensity = pow(max(dot(R,C),specular_power)
         R = 2.0*dot(I.normalized(),same_side_normal)*same_side_normal-I.normalized();
        double s_intensity =pow(( std::max(dot(R,(ray.direction).normalized()*(-1.0)),0.0)),specular_power);
        
        color += diff_color*color_specular*s_intensity/dot(I,I);

    }

    // TODO: determine the color
    return color;
}
