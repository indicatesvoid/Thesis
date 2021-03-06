uniform sampler2D tex;
uniform float xPixels;
uniform float yPixels;

void main()
{
    vec2 texCoords = vec2(floor(gl_TexCoord[0].s * xPixels) / xPixels, floor(gl_TexCoord[0].t * yPixels) / yPixels);
    gl_FragColor = texture2D(tex, texCoords);
}