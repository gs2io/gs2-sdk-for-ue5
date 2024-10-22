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
    class FGetMaxStaminaTableMasterRequest;

    class GS2STAMINA_API FGetMaxStaminaTableMasterRequest final : public TSharedFromThis<FGetMaxStaminaTableMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MaxStaminaTableNameValue;
        
    public:
        
        FGetMaxStaminaTableMasterRequest();
        FGetMaxStaminaTableMasterRequest(
            const FGetMaxStaminaTableMasterRequest& From
        );
        ~FGetMaxStaminaTableMasterRequest() = default;

        TSharedPtr<FGetMaxStaminaTableMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMaxStaminaTableMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMaxStaminaTableMasterRequest> WithMaxStaminaTableName(const TOptional<FString> MaxStaminaTableName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMaxStaminaTableName() const;

        static TSharedPtr<FGetMaxStaminaTableMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMaxStaminaTableMasterRequest> FGetMaxStaminaTableMasterRequestPtr;
}