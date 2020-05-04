//
//  Text.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <string>
#include "Peripheral.hpp"
#include "ContainerFrame.hpp"


class Text : public Peripheral
{
public:
    Text(std::string txt, const int x, const int y, const bool frame);
    Text(std::string txt, const float x, const float y, const bool frame);
    ~Text();
    
    void update(const Uint32 dt) override;
    builder_pack builder_function() const override;
    
    void set_text(std::string txt);
    void add_shadow();
    
private:
    std::string text_;
    ContainerFrame* text_frame_;
};
