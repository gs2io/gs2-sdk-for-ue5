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

namespace Gs2::Stamina::Request
{
    class FGetRecoverIntervalTableMasterRequest;

    class GS2STAMINA_API FGetRecoverIntervalTableMasterRequest final : public TSharedFromThis<FGetRecoverIntervalTableMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RecoverIntervalTableNameValue;
        
    public:
        
        FGetRecoverIntervalTableMasterRequest();
        FGetRecoverIntervalTableMasterRequest(
            const FGetRecoverIntervalTableMasterRequest& From
        );
        ~FGetRecoverIntervalTableMasterRequest() = default;

        TSharedPtr<FGetRecoverIntervalTableMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRecoverIntervalTableMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRecoverIntervalTableMasterRequest> WithRecoverIntervalTableName(const TOptional<FString> RecoverIntervalTableName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRecoverIntervalTableName() const;

        static TSharedPtr<FGetRecoverIntervalTableMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRecoverIntervalTableMasterRequest, ESPMode::ThreadSafe> FGetRecoverIntervalTableMasterRequestPtr;
}