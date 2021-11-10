// This shader is from raylib's github. It is not our creation, since we only edited it to fit our needs.

#version 100

precision mediump float;

// Input vertex attributes (from vertex shader).
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values.
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Custom variables.
float offset = 0.0;
float frequency = 450. / 3.;

void main()
{
    float globalPos = (fragTexCoord.y + offset) * frequency;
    float wavePos = cos((fract(globalPos) - 0.5) * 3.14 / 2.);

    // Fetching texel color from texture sampler.
    vec4 texelColor = texture2D(texture0, fragTexCoord);

    gl_FragColor = mix(vec4(0.3, 0.3, 0.3, 0.), texelColor, wavePos);
}
