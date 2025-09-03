xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 18;
 60.02865;-28.02727;24.29341;,
 -1.68829;-16.03078;48.37485;,
 -2.40307;-78.30690;47.59664;,
 59.45103;-78.34016;23.66478;,
 55.87635;-85.23698;-141.85966;,
 6.57310;-84.10571;-190.60728;,
 7.14185;-34.60406;-189.98881;,
 56.49431;-31.43177;-141.18754;,
 3.54464;20.22765;-83.81748;,
 63.84950;-2.36069;-74.26113;,
 -1.68829;-16.03078;48.37485;,
 60.02865;-28.02727;24.29341;,
 -61.05844;-24.53105;4.66005;,
 -61.63629;-74.84327;4.03137;,
 -55.73351;-82.07222;-150.47707;,
 -55.15638;-31.75954;-149.84838;,
 -57.23751;1.13590;-93.89439;,
 -61.05844;-24.53105;4.66005;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;1,12,13,2;,
 4;5,14,15,6;,
 4;6,15,16,8;,
 4;8,16,17,10;,
 3;3,4,11;,
 3;11,4,9;,
 3;9,4,7;,
 3;13,14,2;,
 3;14,5,2;,
 3;2,5,3;,
 3;3,5,4;,
 3;14,13,15;,
 3;15,13,16;,
 3;16,13,12;;
 
 MeshMaterialList {
  2;
  18;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.062745;0.062745;0.062745;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.360789;-0.015794;0.932514;,
  0.975343;-0.033121;-0.218194;,
  0.813210;0.324618;-0.483024;,
  0.351670;0.932567;-0.081532;,
  -0.132208;-0.010867;0.991162;,
  0.703098;0.000807;-0.711092;,
  0.345072;0.680901;-0.645987;,
  0.035927;0.993057;-0.112015;,
  -0.900245;0.004898;0.435356;,
  -0.981972;0.007184;0.188892;,
  -0.868260;0.016158;-0.495846;,
  -0.432798;0.495776;-0.752922;,
  -0.286313;0.949149;-0.130924;,
  -0.012544;0.966112;0.257817;,
  0.293380;0.920625;0.257637;,
  -0.541019;0.016717;-0.840844;,
  -0.317269;0.919182;0.233334;,
  0.999714;-0.011213;-0.021123;,
  0.998298;-0.058100;-0.004943;,
  0.997233;-0.057639;-0.046956;,
  -0.089897;-0.995017;0.043119;,
  -0.053672;-0.997999;0.033423;,
  -0.032783;-0.998996;0.030519;,
  -0.024580;-0.999234;0.030450;,
  -0.028186;-0.999030;0.033837;,
  -0.065341;-0.996938;0.042950;,
  -0.999176;0.008803;-0.039611;,
  -0.999237;0.008791;-0.038064;;
  18;
  4;0,4,4,0;,
  4;1,5,6,2;,
  4;2,6,7,3;,
  4;3,7,13,14;,
  4;4,8,9,4;,
  4;15,10,11,15;,
  4;6,11,12,7;,
  4;7,12,16,13;,
  3;17,1,18;,
  3;18,1,19;,
  3;19,1,2;,
  3;20,21,22;,
  3;21,23,22;,
  3;22,23,24;,
  3;24,23,25;,
  3;10,9,26;,
  3;26,9,27;,
  3;27,9,8;;
 }
 MeshTextureCoords {
  18;
  0.000000;0.250000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.250000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.666670;0.250000;,
  0.833330;0.500000;,
  0.833330;0.250000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.000000;0.750000;,
  0.166670;0.750000;,
  0.500000;0.750000;,
  0.666670;0.750000;,
  0.833330;0.750000;,
  1.000000;0.750000;;
 }
}
