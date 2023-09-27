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

#include "Formation/Domain/Model/Gs2FormationEzUserGameSessionDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzUserGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
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
        Gs2::Formation::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldsIteratorPtr FEzUserGameSessionDomain::Molds(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldsIterator>(
            Domain->Molds(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeMolds(TFunction<void()> Callback)
    {
        return Domain->SubscribeMolds(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeMolds(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeMolds(
            CallbackId
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzMoldGameSessionDomainPtr FEzUserGameSessionDomain::Mold(
        const FString MoldModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzMoldGameSessionDomain>(
            Domain->Mold(
                MoldModelName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribePropertyFormsIteratorPtr FEzUserGameSessionDomain::PropertyForms(
          const FString PropertyFormModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribePropertyFormsIterator>(
            Domain->PropertyForms(
                PropertyFormModelName
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribePropertyForms(TFunction<void()> Callback)
    {
        return Domain->SubscribePropertyForms(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribePropertyForms(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribePropertyForms(
            CallbackId
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomainPtr FEzUserGameSessionDomain::PropertyForm(
        const FString PropertyFormModelName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomain>(
            Domain->PropertyForm(
                PropertyFormModelName,
                PropertyId
            ),
            ProfileValue
        );
    }
}
