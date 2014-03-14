#version 150

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;

uniform SwirlSettings {
  vec2 center;
  float radius;
  float angle;
} ;

vec4 PostFX(sampler2D tex, vec2 uv)
{
  vec2 texSize = vec2(1,1);
  vec2 tc = uv * texSize;
  tc -= center;
  float dist = length(tc);
  if (dist < radius) 
  {
    float percent = (radius - dist) / radius;
    float theta = percent * percent * angle * 8.0;
    float s = sin(theta);
    float c = cos(theta);
    tc = vec2(dot(tc, vec2(c, -s)), dot(tc, vec2(s, c)));
  }
  tc += center;
  vec3 color = texture(tex, tc / texSize).rgb;
  return vec4(color, 1.0);
}

void main (void)
{
  vec2 uv = TexCoord;
  FragColor = PostFX(tex, uv);
}