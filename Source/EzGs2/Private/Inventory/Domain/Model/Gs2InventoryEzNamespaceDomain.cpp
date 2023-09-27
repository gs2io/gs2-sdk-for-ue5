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

#include "Inventory/Domain/Model/Gs2InventoryEzNamespaceDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzNamespaceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzNamespaceDomain::FEzNamespaceDomain(
        Gs2::Inventory::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeInventoryModelsIteratorPtr FEzNamespaceDomain::InventoryModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeInventoryModelsIterator>(
            Domain->InventoryModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeInventoryModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeInventoryModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeInventoryModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeInventoryModels(
            CallbackId
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzInventoryModelDomainPtr FEzNamespaceDomain::InventoryModel(
        const FString InventoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzInventoryModelDomain>(
            Domain->InventoryModel(
                InventoryName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleInventoryModelsIteratorPtr FEzNamespaceDomain::SimpleInventoryModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleInventoryModelsIterator>(
            Domain->SimpleInventoryModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeSimpleInventoryModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeSimpleInventoryModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeSimpleInventoryModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSimpleInventoryModels(
            CallbackId
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzSimpleInventoryModelDomainPtr FEzNamespaceDomain::SimpleInventoryModel(
        const FString InventoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzSimpleInventoryModelDomain>(
            Domain->SimpleInventoryModel(
                InventoryName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigInventoryModelsIteratorPtr FEzNamespaceDomain::BigInventoryModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigInventoryModelsIterator>(
            Domain->BigInventoryModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeBigInventoryModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeBigInventoryModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeBigInventoryModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBigInventoryModels(
            CallbackId
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzBigInventoryModelDomainPtr FEzNamespaceDomain::BigInventoryModel(
        const FString InventoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzBigInventoryModelDomain>(
            Domain->BigInventoryModel(
                InventoryName
            ),
            ProfileValue
        );
    }
}
