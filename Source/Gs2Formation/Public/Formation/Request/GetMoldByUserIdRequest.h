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

namespace Gs2::Formation::Request
{
    class FGetMoldByUserIdRequest;

    class GS2FORMATION_API FGetMoldByUserIdRequest final : public TSharedFromThis<FGetMoldByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldNameValue;
        
    public:
        
        FGetMoldByUserIdRequest();
        FGetMoldByUserIdRequest(
            const FGetMoldByUserIdRequest& From
        );
        ~FGetMoldByUserIdRequest() = default;

        TSharedPtr<FGetMoldByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMoldByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMoldByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetMoldByUserIdRequest> WithMoldName(const TOptional<FString> MoldName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldName() const;

        static TSharedPtr<FGetMoldByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMoldByUserIdRequest, ESPMode::ThreadSafe> FGetMoldByUserIdRequestPtr;
}