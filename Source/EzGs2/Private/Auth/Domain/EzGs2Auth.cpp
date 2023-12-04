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

#include "Auth/Domain/EzGs2Auth.h"

namespace Gs2::UE5::Auth::Domain
{

    FEzGs2Auth::FEzGs2Auth(
        Gs2::Auth::Domain::FGs2AuthDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomainPtr FEzGs2Auth::AccessToken(
    ) const
    {
        return MakeShared<Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomain>(
            Domain->AccessToken(
            ),
            ConnectionValue
        );
    }
}
