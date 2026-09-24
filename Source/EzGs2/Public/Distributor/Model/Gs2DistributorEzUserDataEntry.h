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
#include "Distributor/Model/UserDataEntry.h"

namespace Gs2::UE5::Distributor::Model
{
	class EZGS2_API FEzUserDataEntry final : public TSharedFromThis<FEzUserDataEntry>
	{
        TOptional<FString> ServiceValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> KindValue;
        TOptional<FString> PayloadValue;

	public:
        TSharedPtr<FEzUserDataEntry> WithService(const TOptional<FString> Service);
        TSharedPtr<FEzUserDataEntry> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEzUserDataEntry> WithKind(const TOptional<FString> Kind);
        TSharedPtr<FEzUserDataEntry> WithPayload(const TOptional<FString> Payload);

        TOptional<FString> GetService() const;

        TOptional<FString> GetNamespaceName() const;

        TOptional<FString> GetKind() const;

        TOptional<FString> GetPayload() const;

        Gs2::Distributor::Model::FUserDataEntryPtr ToModel() const;
        static TSharedPtr<FEzUserDataEntry> FromModel(Gs2::Distributor::Model::FUserDataEntryPtr Model);
    };
    typedef TSharedPtr<FEzUserDataEntry> FEzUserDataEntryPtr;
}