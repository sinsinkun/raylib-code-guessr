#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec2 fragPos;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 lightPos;
uniform float lightIntensity;
uniform float lightRadius;
uniform vec3 lightColor;

out vec4 finalColor;

void main() {
  // ambience
  vec3 ambientColor = 0.04 * lightColor;
  
  // falloff from center
  float dist = distance(lightPos, gl_FragCoord.xy); // not normalized
  float volume = max((lightRadius - dist) / lightRadius, 0.0);
  vec3 volumetricColor = lightIntensity * volume * lightColor;

  // diffuse
  vec4 normal = texture(texture0, fragTexCoord);
  if (normal.z > 0.49) {
    // only redistribute normals for coordinates with a valid z normal
    normal = 2.0 * normal - 1.0;
  }
  vec2 lightDir = normalize(lightPos - gl_FragCoord.xy);
  float diffuse = lightIntensity * volume * max(dot(lightDir, normal.xy), 0.0);
  vec3 diffuseColor = diffuse * lightColor;

  // output color
  vec3 color = ambientColor + volumetricColor + diffuseColor;
  finalColor = vec4(color, 1.0);
}