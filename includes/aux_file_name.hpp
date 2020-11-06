// Copyright (c) 2020 Can Boluk
// All rights reserved.   
//    
// Redistribution and use in source and binary forms, with or without   
// modification, are permitted provided that the following conditions are met: 
//    
// 1. Redistributions of source code must retain the above copyright notice,   
//    this list of conditions and the following disclaimer.   
// 2. Redistributions in binary form must reproduce the above copyright   
//    notice, this list of conditions and the following disclaimer in the   
//    documentation and/or other materials provided with the distribution.   
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software 
//    without specific prior written permission.   
//    
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE   
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR   
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF   
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN   
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)   
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  
// POSSIBILITY OF SUCH DAMAGE.        
//
#pragma once
#include <string_view>
#include "common.hpp"
#include "coff_symbol.hpp"

#pragma pack(push, COFF_STRUCT_PACKING)
namespace coff
{
    // Declare the data type.
    //
    struct aux_file_name_t
    {
        char                    file_name[ 18 ];            // Name of the file.

        std::string_view to_string() const
        {
            const char* begin = std::begin( file_name );
            const char* end = std::end( file_name );

            if ( end[ -1 ] ) return { begin, end - begin };
            else             return { begin };
        }
    };
    static_assert( sizeof( aux_file_name_t ) == sizeof( symbol_t ), "Invalid auxiliary symbol." );
    
    // Declare the matching logic.
    //
    template<>
    inline bool symbol_t::has_aux<aux_file_name_t>() const
    {
        return !name.short_cmp( ".file" ) &&
               storage_class == storage_class_t::file_name;
    }
};
#pragma pack(pop)