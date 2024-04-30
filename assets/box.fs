#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec2 fragPos;

out vec4 finalColor;

void main() {
  float r = 1.0 - step(fragPos.x, 1.0 - fragPos.y);
  float g = 1.0 - step(fragPos.x, fragPos.y);
  float b = 0.5;
  
  vec3 color = vec3(r,g,b);
  if (fragPos.x > 0.2 && fragPos.x < 0.8 && fragPos.y > 0.2 && fragPos.y < 0.8) {
    color = vec3(0.5,0.5,1.0);
  }

  finalColor = vec4(color, 1.0);
}