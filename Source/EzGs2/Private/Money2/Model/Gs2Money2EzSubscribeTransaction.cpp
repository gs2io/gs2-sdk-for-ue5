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

#include "Money2/Model/Gs2Money2EzSubscribeTransaction.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransaction::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransaction::WithStore(
        const TOptional<FString> Store
    )
    {
        this->StoreValue = Store;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransaction::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransaction::WithStatusDetail(
        const TOptional<FString> StatusDetail
    )
    {
        this->StatusDetailValue = StatusDetail;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransaction::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzSubscribeTransaction::GetContentName() const
    {
        return ContentNameValue;
    }
    TOptional<FString> FEzSubscribeTransaction::GetStore() const
    {
        return StoreValue;
    }
    TOptional<FString> FEzSubscribeTransaction::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FEzSubscribeTransaction::GetStatusDetail() const
    {
        return StatusDetailValue;
    }
    TOptional<int64> FEzSubscribeTransaction::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FEzSubscribeTransaction::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    Gs2::Money2::Model::FSubscribeTransactionPtr FEzSubscribeTransaction::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FSubscribeTransaction>()
            ->WithContentName(ContentNameValue)
            ->WithStore(StoreValue)
            ->WithTransactionId(TransactionIdValue)
            ->WithStatusDetail(StatusDetailValue)
            ->WithExpiresAt(ExpiresAtValue);
    }

    TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransaction::FromModel(const Gs2::Money2::Model::FSubscribeTransactionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscribeTransaction>()
            ->WithContentName(Model->GetContentName())
            ->WithStore(Model->GetStore())
            ->WithTransactionId(Model->GetTransactionId())
            ->WithStatusDetail(Model->GetStatusDetail())
            ->WithExpiresAt(Model->GetExpiresAt());
    }
}