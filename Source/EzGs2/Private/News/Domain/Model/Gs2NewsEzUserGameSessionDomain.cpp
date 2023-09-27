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

#include "News/Domain/Model/Gs2NewsEzUserGameSessionDomain.h"

namespace Gs2::UE5::News::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::ContentHash() const
    {
        return Domain->ContentHash;
    }

    TOptional<FString> FEzUserGameSessionDomain::TemplateHash() const
    {
        return Domain->TemplateHash;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::News::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::News::Domain::Iterator::FEzDescribeNewsIteratorPtr FEzUserGameSessionDomain::Newses(
    ) const
    {
        return MakeShared<Gs2::UE5::News::Domain::Iterator::FEzDescribeNewsIterator>(
            Domain->Newses(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeNewses(TFunction<void()> Callback)
    {
        return Domain->SubscribeNewses(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeNewses(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeNewses(
            CallbackId
        );
    }

    Gs2::UE5::News::Domain::Model::FEzNewsGameSessionDomainPtr FEzUserGameSessionDomain::News(
    ) const
    {
        return MakeShared<Gs2::UE5::News::Domain::Model::FEzNewsGameSessionDomain>(
            Domain->News(
            ),
            ProfileValue
        );
    }
}
