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
 15;
 242.80906;4.81142;31.71842;,
 33.71340;14.75395;41.71666;,
 31.00839;-19.44834;46.71641;,
 241.94402;-35.92125;32.97784;,
 30.54391;-55.91635;-0.74239;,
 241.56966;-57.46035;-3.53519;,
 26.71171;-29.84448;-49.31021;,
 242.06087;-38.26686;-41.30738;,
 29.42670;12.59346;-53.89961;,
 242.92508;2.46592;-42.56666;,
 34.26020;36.06486;-4.30084;,
 243.29939;24.00480;-6.05377;,
 33.71340;14.75395;41.71666;,
 242.80906;4.81142;31.71842;,
 -1.34982;1.87547;-0.20221;;
 
 16;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 3;1,14,2;,
 3;2,14,4;,
 3;4,14,6;,
 3;6,14,8;,
 3;8,14,10;,
 3;10,14,12;,
 3;3,5,13;,
 3;13,5,11;,
 3;5,7,11;,
 3;11,7,9;;
 
 MeshMaterialList {
  2;
  16;
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
   0.645333;0.138039;0.020706;1.000000;;
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
  23;
  0.068867;0.564739;0.822391;,
  0.060693;0.084965;0.994534;,
  -0.010918;-0.828576;0.559770;,
  0.015454;-0.548601;-0.835942;,
  0.041705;-0.071076;-0.996599;,
  0.064340;0.997747;-0.019021;,
  -0.398728;0.563649;0.723405;,
  -0.614936;-0.087473;0.783711;,
  -0.663905;-0.690467;0.287203;,
  -0.356636;0.934208;0.008102;,
  -0.970634;-0.226225;0.081809;,
  -0.014730;-0.886491;-0.462512;,
  0.055539;0.880689;-0.470427;,
  -0.342849;0.851845;-0.395999;,
  -0.901443;-0.245933;-0.356254;,
  -0.867751;0.001768;-0.496996;,
  -0.690296;0.722818;0.032023;,
  0.999774;-0.021163;0.002234;,
  0.999774;-0.021160;0.002237;,
  0.999774;-0.021161;0.002230;,
  0.999774;-0.021154;0.002233;,
  0.999774;-0.021151;0.002237;,
  0.999774;-0.021143;0.002223;;
  16;
  4;0,6,7,1;,
  4;2,2,8,2;,
  4;11,11,3,3;,
  4;3,3,4,4;,
  4;12,13,9,5;,
  4;5,9,6,0;,
  3;6,10,7;,
  3;7,10,8;,
  3;8,10,14;,
  3;14,10,15;,
  3;13,16,9;,
  3;9,16,6;,
  3;17,18,19;,
  3;19,18,20;,
  3;18,21,20;,
  3;20,21,22;;
 }
 MeshTextureCoords {
  15;
  0.000000;0.250000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.250000;,
  0.333330;0.500000;,
  0.333330;0.250000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.666670;0.500000;,
  0.666670;0.250000;,
  0.833330;0.500000;,
  0.833330;0.250000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.500000;0.865380;;
 }
}
