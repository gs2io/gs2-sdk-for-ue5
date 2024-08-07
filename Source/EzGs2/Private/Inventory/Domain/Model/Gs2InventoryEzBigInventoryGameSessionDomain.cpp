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

#include "Inventory/Domain/Model/Gs2InventoryEzBigInventoryGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzBigInventoryGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzBigInventoryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBigInventoryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzBigInventoryGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzBigInventoryGameSessionDomain::FEzBigInventoryGameSessionDomain(
        Gs2::Inventory::Domain::Model::FBigInventoryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigItemsIteratorPtr FEzBigInventoryGameSessionDomain::BigItems(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigItemsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzBigInventoryGameSessionDomain::SubscribeBigItems(TFunction<void()> Callback)
    {
        return Domain->SubscribeBigItems(
            Callback
        );
    }

    void FEzBigInventoryGameSessionDomain::UnsubscribeBigItems(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBigItems(
            CallbackId
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomainPtr FEzBigInventoryGameSessionDomain::BigItem(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomain>(
            Domain->BigItem(
                ItemName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
