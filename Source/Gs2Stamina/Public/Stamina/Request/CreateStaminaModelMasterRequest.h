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
    class FCreateStaminaModelMasterRequest;

    class GS2STAMINA_API FCreateStaminaModelMasterRequest final : public TSharedFromThis<FCreateStaminaModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
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
        
        FCreateStaminaModelMasterRequest();
        FCreateStaminaModelMasterRequest(
            const FCreateStaminaModelMasterRequest& From
        );
        ~FCreateStaminaModelMasterRequest() = default;

        TSharedPtr<FCreateStaminaModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithIsOverflow(const TOptional<bool> IsOverflow);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithMaxStaminaTableName(const TOptional<FString> MaxStaminaTableName);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithRecoverIntervalTableName(const TOptional<FString> RecoverIntervalTableName);
        TSharedPtr<FCreateStaminaModelMasterRequest> WithRecoverValueTableName(const TOptional<FString> RecoverValueTableName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
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

        static TSharedPtr<FCreateStaminaModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateStaminaModelMasterRequest> FCreateStaminaModelMasterRequestPtr;
}