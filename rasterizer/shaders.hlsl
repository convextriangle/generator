//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
{
    PSInput result;

    result.position = position;
    result.color = color;

    return result;
}

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

float4 PSMain(PSInput input) : SV_TARGET
{
    uint sampling = g_texture.Sample(g_sampler, input.position.xy);
    float4 unpackedColor = float4(
    ((sampling >> 0) & 0xFF) / 255.0f,
    ((sampling >> 8) & 0xFF) / 255.0f,
    ((sampling >> 16) & 0xFF) / 255.0f,
    ((sampling >> 24) & 0xFF) / 255.0f
);
    return unpackedColor;
}