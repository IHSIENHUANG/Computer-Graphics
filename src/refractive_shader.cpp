#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"
#define DEBUG 1
vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. 
        //      If so update the reflectance_ratio for total internal refraction
        //
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //
        vec3 T; //Refrection_direcition
        //double cos_thetar;
        double ni=1.0;
        double nr=refractive_index;
        //vec3 d =  (intersection_point - ray.endpoint).normalized();
        vec3 d = ray.direction;
        double cos_theta1=dot((-1.0)*d,same_side_normal);
        double n=0.0;
            if(is_exiting)//object to air
            {
                ni=refractive_index;
                nr=1.0;
            }
            else
            {
                ni =1.0;
                nr = refractive_index;    
            }
            
            n=ni/nr;
           // cos_thetar = sqrt(1-pow(ni/nr,2)*(1-pow(cos_theta1,2)));//calculare cos_thetar
           // double tem = 1-pow((ni/nr),2)
           
               double tem = 1 - n*n * (1 - pow(cos_theta1, 2));
               double cos_thetar = sqrt(tem);

           if(tem<0)
           {
                reflectance_ratio =1;
                    
           }
           else
           {
            
            T = (-1.0)*cos_thetar*same_side_normal + n*(d-dot(d,same_side_normal.normalized())*same_side_normal.normalized());
            //vec3 T = (-1.0)*cos_thetar*same_side_normal + n*(d+cos_theta1*same_side_normal);
            //vec3 T = (ni/nr) * (d + cos_theta1 * same_side_normal) - cos_thetar * same_side_normal;
            Ray new_ray22 = Ray(intersection_point,T);
            refraction_color += world.Cast_Ray(new_ray22,recursion_depth+1);

            
            double R_parallel =pow((nr*cos_theta1-ni*cos_thetar)/(nr*cos_theta1+ni*cos_thetar),2);
            double R_normal   =pow((ni*cos_theta1-nr*cos_thetar)/(ni*cos_theta1+nr*cos_thetar),2);
                reflectance_ratio = (R_parallel + R_normal)/2 ; 
            }                                

            //count out new ray direction
           // Ray new_ray2(intersection_point,T);
           // refraction_color += world.Cast_Ray(new_ray2,++recursion_depth);
            
            
            
            
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        //
        
        vec3 CR2,C0,R;
        vec3 RD = (-1.0)*ray.direction;
        R = 2.0*dot(RD.normalized(),same_side_normal)*same_side_normal-RD.normalized();
        Ray New_Ray(intersection_point,R);
        CR2 = world.Cast_Ray(New_Ray,++recursion_depth);
        reflection_color = CR2;
        
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    //
    color +=  reflectance_ratio * reflection_color + (1.0-reflectance_ratio)* refraction_color;
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

