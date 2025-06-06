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

#include "Money2/Domain/Model/Gs2Money2EzUserDomain.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>> FEzUserDomain::WithdrawTransactions() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>>();
            for (auto Value : *Domain->WithdrawTransactions) {
                Result->Add(
                    Gs2::UE5::Money2::Model::FEzDepositTransaction::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::Money2::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Money2::Domain::Model::FEzWalletDomainPtr FEzUserDomain::Wallet(
        const int32 Slot
    ) const
    {
        return MakeShared<Gs2::UE5::Money2::Domain::Model::FEzWalletDomain>(
            Domain->Wallet(
                Slot
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusDomainPtr FEzUserDomain::SubscriptionStatus(
        const FString ContentName
    ) const
    {
        return MakeShared<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusDomain>(
            Domain->SubscriptionStatus(
                ContentName
            ),
            ConnectionValue
        );
    }
}
