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

#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomShowcaseGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzRandomShowcaseGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRandomShowcaseGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRandomShowcaseGameSessionDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    FEzRandomShowcaseGameSessionDomain::FEzRandomShowcaseGameSessionDomain(
        Gs2::Showcase::Domain::Model::FRandomShowcaseAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Showcase::Domain::Iterator::FEzDescribeRandomDisplayItemsIteratorPtr FEzRandomShowcaseGameSessionDomain::RandomDisplayItems(
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Iterator::FEzDescribeRandomDisplayItemsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzRandomShowcaseGameSessionDomain::SubscribeRandomDisplayItems(TFunction<void()> Callback)
    {
        return Domain->SubscribeRandomDisplayItems(
            Callback
        );
    }

    void FEzRandomShowcaseGameSessionDomain::UnsubscribeRandomDisplayItems(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeRandomDisplayItems(
            CallbackId
        );
    }

    Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomainPtr FEzRandomShowcaseGameSessionDomain::RandomDisplayItem(
        const FString DisplayItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomain>(
            Domain->RandomDisplayItem(
                DisplayItemName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
