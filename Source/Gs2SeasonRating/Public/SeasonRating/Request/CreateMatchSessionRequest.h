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

namespace Gs2::SeasonRating::Request
{
    class FCreateMatchSessionRequest;

    class GS2SEASONRATING_API FCreateMatchSessionRequest final : public TSharedFromThis<FCreateMatchSessionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SessionNameValue;
        TOptional<int32> TtlSecondsValue;
        
    public:
        
        FCreateMatchSessionRequest();
        FCreateMatchSessionRequest(
            const FCreateMatchSessionRequest& From
        );
        ~FCreateMatchSessionRequest() = default;

        TSharedPtr<FCreateMatchSessionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateMatchSessionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateMatchSessionRequest> WithSessionName(const TOptional<FString> SessionName);
        TSharedPtr<FCreateMatchSessionRequest> WithTtlSeconds(const TOptional<int32> TtlSeconds);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSessionName() const;
        TOptional<int32> GetTtlSeconds() const;
        FString GetTtlSecondsString() const;

        static TSharedPtr<FCreateMatchSessionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateMatchSessionRequest> FCreateMatchSessionRequestPtr;
}