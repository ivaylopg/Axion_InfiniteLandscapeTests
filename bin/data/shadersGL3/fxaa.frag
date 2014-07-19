#version 150

uniform sampler2DRect tex0;
in vec2 texCoordVarying;
out vec4 outputColor;

//uniform vec2 resolution;

vec2 resolution;

//varying vec2 vUv;

const float FXAA_REDUCE_MIN = 1.0/128.0;
const float FXAA_REDUCE_MUL = 1.0/1024.0;
const float FXAA_SPAN_MAX = 8.0;

void main() {
    
    //vec4 color = vec4(1.0,1.0,1.0,1.0);
    
    resolution = vec2(1.f,1.f);
    
    vec3 rgbNW = texture( tex0, ( texCoordVarying.xy + vec2( -1.0, -1.0 ) ) * resolution ).xyz;
    vec3 rgbNE = texture( tex0, ( texCoordVarying.xy + vec2( 1.0, -1.0 ) ) * resolution ).xyz;
    vec3 rgbSW = texture( tex0, ( texCoordVarying.xy + vec2( -1.0, 1.0 ) ) * resolution ).xyz;
    vec3 rgbSE = texture( tex0, ( texCoordVarying.xy + vec2( 1.0, 1.0 ) ) * resolution ).xyz;
    vec4 rgbaM  = texture( tex0,  texCoordVarying.xy  * resolution );
    vec3 rgbM  = rgbaM.xyz;
    float opacity  = rgbaM.w;
    
    vec3 luma = vec3( 0.299, 0.587, 0.114 );
    
    float lumaNW = dot( rgbNW, luma );
    float lumaNE = dot( rgbNE, luma );
    float lumaSW = dot( rgbSW, luma );
    float lumaSE = dot( rgbSE, luma );
    float lumaM  = dot( rgbM,  luma );
    float lumaMin = min( lumaM, min( min( lumaNW, lumaNE ), min( lumaSW, lumaSE ) ) );
    float lumaMax = max( lumaM, max( max( lumaNW, lumaNE) , max( lumaSW, lumaSE ) ) );
    
    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
    float dirReduce = max( ( lumaNW + lumaNE + lumaSW + lumaSE ) * ( 0.25 * FXAA_REDUCE_MUL ), FXAA_REDUCE_MIN );
    
    float rcpDirMin = 1.0 / ( min( abs( dir.x ), abs( dir.y ) ) + dirReduce );
    dir = min( vec2( FXAA_SPAN_MAX,  FXAA_SPAN_MAX),
              max( vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
                  dir * rcpDirMin)) * resolution;
    
    vec3 rgbA = 0.5 * (
                       texture( tex0, texCoordVarying.xy  * resolution + dir * ( 1.0 / 3.0 - 0.5 ) ).xyz +
                       texture( tex0, texCoordVarying.xy  * resolution + dir * ( 2.0 / 3.0 - 0.5 ) ).xyz );
    
    vec3 rgbB = rgbA * 0.5 + 0.25 * (
                                     texture( tex0, texCoordVarying.xy  * resolution + dir * -0.5 ).xyz +
                                     texture( tex0, texCoordVarying.xy  * resolution + dir * 0.5 ).xyz );
    
    float lumaB = dot( rgbB, luma );
    
    if ( ( lumaB < lumaMin ) || ( lumaB > lumaMax ) ) {
        
        outputColor = vec4( rgbA, opacity );
        
    } else {
        
        outputColor = vec4( rgbB, opacity );
        
    }
    
}

/*
 #version 150
 
 uniform sampler2DRect tex0;
 uniform float blurAmnt;
 
 in vec2 texCoordVarying;
 out vec4 outputColor;
 
 void main()
 {
 
 vec4 color = vec4(1.0,1.0,1.0,1.0);
 
 color += 1.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * -4.0, 0.0));
 color += 2.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * -3.0, 0.0));
 color += 3.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * -2.0, 0.0));
 color += 4.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * -1.0, 0.0));
 
 color += 5.0 * texture(tex0, texCoordVarying + vec2(blurAmnt, 0));
 
 color += 4.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * 1.0, 0.0));
 color += 3.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * 2.0, 0.0));
 color += 2.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * 3.0, 0.0));
 color += 1.0 * texture(tex0, texCoordVarying + vec2(blurAmnt * 4.0, 0.0));
 
 color /= 25.0;
 
 outputColor = color;
 }
 */

/*
void main() {
    outputColor = vec4(1.0,0.0,0.0,1.0);
}
*/