#pragma once

#include <map>
#include <string>
#include <optional>
#include "gpds_export.h"
#include "types.h"
#include "utils.h"

namespace Gpds
{

    class GPDS_EXPORT Attributes
    {
    public:
        std::map<gString, gString> map;

        Attributes( ) = default;
        Attributes( const Attributes& other );
        Attributes( Attributes&& other );
        virtual ~Attributes( ) = default;

        template<typename T>
        void add(gString&& key, const T& value)
        {
            map.emplace( std::forward< gString >( key ), valueToString( value ) );
        }

        template<typename T>
        std::optional<T> get(const gString& key) const
        {
            // Get string
            std::string valueString;
            for ( auto it = map.cbegin(); it != map.cend(); ++it ) {
                if ( it->first == key ) {
                    valueString = it->second;
                    break;
                }
            }
            if ( valueString.empty() ) {
                return std::nullopt;
            }

            return stringToValue<T>( valueString );
        }

    };

}
