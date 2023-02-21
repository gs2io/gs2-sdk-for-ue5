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

#include "Gateway/Model/FirebaseToken.h"

namespace Gs2::Gateway::Model
{
    FFirebaseToken::FFirebaseToken():
        FirebaseTokenIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TokenValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FFirebaseToken::FFirebaseToken(
        const FFirebaseToken& From
    ):
        FirebaseTokenIdValue(From.FirebaseTokenIdValue),
        UserIdValue(From.UserIdValue),
        TokenValue(From.TokenValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FFirebaseToken> FFirebaseToken::WithFirebaseTokenId(
        const TOptional<FString> FirebaseTokenId
    )
    {
        this->FirebaseTokenIdValue = FirebaseTokenId;
        return SharedThis(this);
    }

    TSharedPtr<FFirebaseToken> FFirebaseToken::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FFirebaseToken> FFirebaseToken::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FFirebaseToken> FFirebaseToken::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FFirebaseToken> FFirebaseToken::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FFirebaseToken::GetFirebaseTokenId() const
    {
        return FirebaseTokenIdValue;
    }
    TOptional<FString> FFirebaseToken::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FFirebaseToken::GetToken() const
    {
        return TokenValue;
    }
    TOptional<int64> FFirebaseToken::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FFirebaseToken::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FFirebaseToken::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FFirebaseToken::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FFirebaseToken::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):gateway:(?<namespaceName>.+):user:(?<userId>.+):firebase:token"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FFirebaseToken::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):gateway:(?<namespaceName>.+):user:(?<userId>.+):firebase:token"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FFirebaseToken::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):gateway:(?<namespaceName>.+):user:(?<userId>.+):firebase:token"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FFirebaseToken::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):gateway:(?<namespaceName>.+):user:(?<userId>.+):firebase:token"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FFirebaseToken> FFirebaseToken::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFirebaseToken>()
            ->WithFirebaseTokenId(Data->HasField("firebaseTokenId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("firebaseTokenId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithToken(Data->HasField("token") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("token", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FFirebaseToken::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (FirebaseTokenIdValue.IsSet())
        {
            JsonRootObject->SetStringField("firebaseTokenId", FirebaseTokenIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TokenValue.IsSet())
        {
            JsonRootObject->SetStringField("token", TokenValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FFirebaseToken::TypeName = "FirebaseToken";
}