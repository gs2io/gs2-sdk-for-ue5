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
#include "Dom/JsonObject.h"

namespace Gs2::Stamina::Request
{
    class FUpdateStaminaModelMasterRequest;

    class GS2STAMINA_API FUpdateStaminaModelMasterRequest final : public TSharedFromThis<FUpdateStaminaModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<bool> IsOverflowValue;
        TOptional<int32> MaxCapacityValue;
        TOptional<FString> MaxStaminaTableNameValue;
        TOptional<FString> RecoverIntervalTableNameValue;
        TOptional<FString> RecoverValueTableNameValue;
        
    public:
        
        FUpdateStaminaModelMasterRequest();
        FUpdateStaminaModelMasterRequest(
            const FUpdateStaminaModelMasterRequest& From
        );
        ~FUpdateStaminaModelMasterRequest() = default;

        TSharedPtr<FUpdateStaminaModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithIsOverflow(const TOptional<bool> IsOverflow);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithMaxStaminaTableName(const TOptional<FString> MaxStaminaTableName);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithRecoverIntervalTableName(const TOptional<FString> RecoverIntervalTableName);
        TSharedPtr<FUpdateStaminaModelMasterRequest> WithRecoverValueTableName(const TOptional<FString> RecoverValueTableName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetRecoverIntervalMinutes() const;
        FString GetRecoverIntervalMinutesString() const;
        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;
        TOptional<int32> GetInitialCapacity() const;
        FString GetInitialCapacityString() const;
        TOptional<bool> GetIsOverflow() const;
        FString GetIsOverflowString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;
        TOptional<FString> GetMaxStaminaTableName() const;
        TOptional<FString> GetRecoverIntervalTableName() const;
        TOptional<FString> GetRecoverValueTableName() const;

        static TSharedPtr<FUpdateStaminaModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStaminaModelMasterRequest> FUpdateStaminaModelMasterRequestPtr;
}