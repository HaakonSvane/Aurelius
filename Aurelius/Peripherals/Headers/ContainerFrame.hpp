//
//  ContainerFrame.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include "Peripheral.hpp"

class ContainerFrame : public Peripheral
{
public:
    ContainerFrame(const int x, const int y, int width, int height);
    ContainerFrame(const float x, const float y, const int width, const int height);
    
    ~ContainerFrame() = default;
    
    void update(Uint32 dt) override{return;};
    virtual builder_pack builder_function() const override;
    
private:
    int width_;
    int height_;
};
