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

#include "Distributor/Model/Gs2DistributorEzUserDataEntry.h"

namespace Gs2::UE5::Distributor::Model
{

    TSharedPtr<FEzUserDataEntry> FEzUserDataEntry::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FEzUserDataEntry> FEzUserDataEntry::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FEzUserDataEntry> FEzUserDataEntry::WithKind(
        const TOptional<FString> Kind
    )
    {
        this->KindValue = Kind;
        return SharedThis(this);
    }

    TSharedPtr<FEzUserDataEntry> FEzUserDataEntry::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }
    TOptional<FString> FEzUserDataEntry::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FEzUserDataEntry::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }
    TOptional<FString> FEzUserDataEntry::GetKind() const
    {
        return KindValue;
    }
    TOptional<FString> FEzUserDataEntry::GetPayload() const
    {
        return PayloadValue;
    }

    Gs2::Distributor::Model::FUserDataEntryPtr FEzUserDataEntry::ToModel() const
    {
        return MakeShared<Gs2::Distributor::Model::FUserDataEntry>()
            ->WithService(ServiceValue)
            ->WithNamespaceName(NamespaceNameValue)
            ->WithKind(KindValue)
            ->WithPayload(PayloadValue);
    }

    TSharedPtr<FEzUserDataEntry> FEzUserDataEntry::FromModel(const Gs2::Distributor::Model::FUserDataEntryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUserDataEntry>()
            ->WithService(Model->GetService())
            ->WithNamespaceName(Model->GetNamespaceName())
            ->WithKind(Model->GetKind())
            ->WithPayload(Model->GetPayload());
    }
}