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
    class FGetRecoverValueTableMasterRequest;

    class GS2STAMINA_API FGetRecoverValueTableMasterRequest final : public TSharedFromThis<FGetRecoverValueTableMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RecoverValueTableNameValue;
        
    public:
        
        FGetRecoverValueTableMasterRequest();
        FGetRecoverValueTableMasterRequest(
            const FGetRecoverValueTableMasterRequest& From
        );
        ~FGetRecoverValueTableMasterRequest() = default;

        TSharedPtr<FGetRecoverValueTableMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRecoverValueTableMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRecoverValueTableMasterRequest> WithRecoverValueTableName(const TOptional<FString> RecoverValueTableName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRecoverValueTableName() const;

        static TSharedPtr<FGetRecoverValueTableMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRecoverValueTableMasterRequest> FGetRecoverValueTableMasterRequestPtr;
}