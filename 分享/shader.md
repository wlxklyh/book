
```cpp
https://www.shadertoy.com/view/WtXXDl

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // UV坐标标准化为 0 - 1
    vec2 uv = fragCoord/iResolution.xy;
    // 模糊后的颜色
    vec4 clraverge = vec4(0.0, 0.0, 0.0, 0.0);
    // 模糊范围
    float range = 20.0, count = 0.0, x1, y1;
    
    // 中心点
    vec2 cpos = vec2(0.5, 0.5);
    
    
    // float xOfferSet = abs(uv.x - cpos.x);
    // float yOfferSet = abs(uv.y - cpos.y);
    // if((xOfferSet < 0.2 && xOfferSet > 0.0)&&
    // (yOfferSet < 0.2 && yOfferSet > 0.0) ){
    //     fragColor = texture(iChannel0, vec2(uv.x, uv.y));
    //     return ;
    // }
    
    // 遍历模糊
    for (float j = 1.0; j <= range; j += 1.0)
    {
        // 连线的斜率
        float k = (cpos.y - uv.y) / (cpos.x - uv.x);
        // X轴上采样 偏移越来越小
        x1 = uv.x + (cpos.x - uv.x) * j / (10.0 * range);
        // Y轴按照X轴采样
        y1 = cpos.y - (cpos.x - x1) * k;
        // 边界保护
        if (x1 < 0.0 || y1 < 0.0 || x1 > 1.0 || y1 > 1.0)
        {
            continue;
        }
        clraverge += texture(iChannel0, vec2(x1, y1));
        count += 1.0;
    }
    clraverge /= count;
    fragColor = clraverge;
}
```
