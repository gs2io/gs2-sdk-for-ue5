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

#include "Auth/Model/AccessToken.h"

namespace Gs2::Auth::Model
{
    FAccessToken::FAccessToken():
        TokenValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        FederationFromUserIdValue(TOptional<FString>()),
        ExpireValue(TOptional<int64>()),
        TimeOffsetValue(TOptional<int32>())
    {
    }

    FAccessToken::FAccessToken(
        const FAccessToken& From
    ):
        TokenValue(From.TokenValue),
        UserIdValue(From.UserIdValue),
        FederationFromUserIdValue(From.FederationFromUserIdValue),
        ExpireValue(From.ExpireValue),
        TimeOffsetValue(From.TimeOffsetValue)
    {
    }

    TSharedPtr<FAccessToken> FAccessToken::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithFederationFromUserId(
        const TOptional<FString> FederationFromUserId
    )
    {
        this->FederationFromUserIdValue = FederationFromUserId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithExpire(
        const TOptional<int64> Expire
    )
    {
        this->ExpireValue = Expire;
        return SharedThis(this);
    }

    TSharedPtr<FAccessToken> FAccessToken::WithTimeOffset(
        const TOptional<int32> TimeOffset
    )
    {
        this->TimeOffsetValue = TimeOffset;
        return SharedThis(this);
    }
    TOptional<FString> FAccessToken::GetToken() const
    {
        return TokenValue;
    }
    TOptional<FString> FAccessToken::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FAccessToken::GetFederationFromUserId() const
    {
        return FederationFromUserIdValue;
    }
    TOptional<int64> FAccessToken::GetExpire() const
    {
        return ExpireValue;
    }

    FString FAccessToken::GetExpireString() const
    {
        if (!ExpireValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpireValue.GetValue());
    }
    TOptional<int32> FAccessToken::GetTimeOffset() const
    {
        return TimeOffsetValue;
    }

    FString FAccessToken::GetTimeOffsetString() const
    {
        if (!TimeOffsetValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TimeOffsetValue.GetValue());
    }

    TSharedPtr<FAccessToken> FAccessToken::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAccessToken>()
            ->WithToken(Data->HasField(ANSI_TO_TCHAR("token")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("token"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFederationFromUserId(Data->HasField(ANSI_TO_TCHAR("federationFromUserId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("federationFromUserId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpire(Data->HasField(ANSI_TO_TCHAR("expire")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expire"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithTimeOffset(Data->HasField(ANSI_TO_TCHAR("timeOffset")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timeOffset"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FAccessToken::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("token"), TokenValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (FederationFromUserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("federationFromUserId"), FederationFromUserIdValue.GetValue());
        }
        if (ExpireValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("expire"), FString::Printf(TEXT("%lld"), ExpireValue.GetValue()));
        }
        if (TimeOffsetValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("timeOffset"), TimeOffsetValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAccessToken::TypeName = "AccessToken";
}
#include "Auth/Model/Cache/AccessToken.h"

namespace Gs2::Auth::Model::Cache
{
    FString FAccessTokenCache::CreateCacheParentKey(
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("auth:")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":AccessToken");
    }

    FString FAccessTokenCache::CreateCacheKey(
    )
    {
        return FString("Singleton");
    }

    bool FAccessTokenCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Auth::Model::FAccessTokenPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Auth::Model::FAccessToken>(
            CreateCacheParentKey(
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FAccessTokenCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Auth::Model::FAccessTokenPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Auth::Model::FAccessToken::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FAccessTokenCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Auth::Model::FAccessToken::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccessTokenCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Auth::Model::FAccessTokenPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Auth::Model::FAccessTokenPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Auth::Model::FAccessTokenPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("accessToken"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FAccessTokenCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Auth::Model::FAccessTokenPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Auth::Model::FAccessToken::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Auth::Model::FAccessTokenPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Auth::Model::FAccessToken>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FAccessTokenCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Auth::Model::FAccessToken::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}