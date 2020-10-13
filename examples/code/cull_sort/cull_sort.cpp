#include "../example_common.h"

using namespace put;
using namespace ecs;

namespace pen
{
    pen_creation_params pen_entry(int argc, char** argv)
    {
        pen::pen_creation_params p;
        p.window_width = 1280;
        p.window_height = 720;
        p.window_title = "cull_sort";
        p.window_sample_count = 4;
        p.user_thread_function = user_setup;
        p.max_renderer_commands = 1<<22;
        p.flags = pen::e_pen_create_flags::renderer;
        return p;
    }
} // namespace pen

void example_setup(ecs::ecs_scene* scene, camera& cam)
{
    scene->view_flags &= ~e_scene_view_flags::hide_debug;
    put::dev_ui::enable(true);

    clear_scene(scene);

    material_resource* default_material = get_material_resource(PEN_HASH("default_material"));
    geometry_resource* box_resource = get_geometry_resource(PEN_HASH("sphere"));

    // add light
    u32 light = get_new_entity(scene);
    scene->names[light] = "front_light";
    scene->id_name[light] = PEN_HASH("front_light");
    scene->lights[light].colour = vec3f::one();
    scene->lights[light].direction = vec3f::one();
    scene->lights[light].type = e_light_type::dir;
    scene->transforms[light].translation = vec3f::zero();
    scene->transforms[light].rotation = quat();
    scene->transforms[light].scale = vec3f::one();
    scene->entities[light] |= e_cmp::light;
    scene->entities[light] |= e_cmp::transform;

    // add some spheres
    f32   num_spheres = 32.0f;
    f32   d = 10.0f;
    vec3f start_pos = vec3f(-d * (num_spheres+1.0f)/2.0f);
    vec3f pos = start_pos;
    for (s32 i = 0; i < num_spheres; ++i)
    {
        pos.x = start_pos.x;
        
        for (s32 i = 0; i < num_spheres; ++i)
        {
            pos.z = start_pos.z;

            for (s32 j = 0; j < num_spheres; ++j)
            {
                u32 s = get_new_entity(scene);
                scene->transforms[s].rotation = quat();
                scene->transforms[s].scale = vec3f(2.0f, 2.0f, 2.0f);
                scene->transforms[s].translation = pos;
                scene->parents[s] = s;
                scene->entities[s] |= e_cmp::transform;

                instantiate_geometry(box_resource, scene, s);
                instantiate_material(default_material, scene, s);
                instantiate_model_cbuffer(scene, s);

                pos.z += d;
            }

            pos.x += d;
        }

        pos.y += d;
    }
}

void example_update(ecs::ecs_scene* scene, camera& cam, f32 dt)
{
}
