/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Auth/Domain/Gs2Auth.h"
#include "Util/Net/Gs2Connection.h"
#include "Auth/Domain/Model/Gs2AuthEzAccessTokenDomain.h"

namespace Gs2::UE5::Auth::Domain
{

    class EZGS2_API FEzGs2Auth {
        Gs2::Auth::Domain::FGs2AuthDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:

        FEzGs2Auth(
            Gs2::Auth::Domain::FGs2AuthDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomainPtr AccessToken(
        ) const;
    };
    typedef TSharedPtr<FEzGs2Auth> FEzGs2AuthPtr;
}
