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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "SeasonRating/Domain/Model/Ballot.h"
#include "SeasonRating/Domain/Model/BallotAccessToken.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::SeasonRating::Domain::Model
{

    FBallotAccessTokenDomain::FBallotAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> SeasonName,
        const TOptional<FString> SessionName,
        const TOptional<int32> NumberOfPlayer,
        const TOptional<FString> KeyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SeasonRating::FGs2SeasonRatingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        SeasonName(SeasonName),
        SessionName(SessionName),
        NumberOfPlayer(NumberOfPlayer),
        KeyId(KeyId),
        ParentKey(Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(NamespaceName, UserId(), AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()))
    {
    }

    FBallotAccessTokenDomain::FBallotAccessTokenDomain(
        const FBallotAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        SeasonName(From.SeasonName),
        SessionName(From.SessionName),
        NumberOfPlayer(From.NumberOfPlayer),
        KeyId(From.KeyId),
        ParentKey(From.ParentKey)
    {

    }

    FBallotAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FBallotAccessTokenDomain>& Self,
        const Request::FGetBallotRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBallotAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FSignedBallot>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSessionName(Self->SessionName)
            ->WithAccessToken(Self->AccessToken.IsValid() ? Self->AccessToken->GetToken() : TOptional<FString>())
            ->WithNumberOfPlayer(Self->NumberOfPlayer)
            ->WithKeyId(Self->KeyId);
        const auto Future = Self->Client->GetBallot(Request);
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Response = Future->GetTask().Result();
        Gs2::SeasonRating::Model::FSignedBallotPtr Value;
        if (Response.IsValid())
        {
            Value = MakeShared<Gs2::SeasonRating::Model::FSignedBallot>()
                ->WithBody(Response->GetBody())
                ->WithSignature(Response->GetSignature());
            Self->Gs2->Cache->Put(
                Gs2::SeasonRating::Model::FSignedBallot::TypeName,
                Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(
                    Request->GetNamespaceName(),
                    Self->UserId(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
                ),
                Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(
                    Request->GetSeasonName(),
                    Request->GetSessionName(),
                    TOptional<int32>(),
                    TOptional<FString>()
                ),
                Value,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        Self->Body = Value.IsValid() ? Value->GetBody() : TOptional<FString>();
        Self->Signature = Value.IsValid() ? Value->GetSignature() : TOptional<FString>();
        *Result = Value;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBallotAccessTokenDomain::FGetTask>> FBallotAccessTokenDomain::Get(
        Request::FGetBallotRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBallotAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SeasonName,
        TOptional<FString> SessionName,
        TOptional<int32> NumberOfPlayer,
        TOptional<FString> KeyId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (SessionName.IsSet() ? *SessionName : "null") + ":" +
            (NumberOfPlayer.IsSet() ? FString::FromInt(*NumberOfPlayer) : "null") + ":" +
            (KeyId.IsSet() ? *KeyId : "null") + ":" +
            ChildType;
    }

    FString FBallotAccessTokenDomain::CreateCacheKey(
        TOptional<FString> SeasonName,
        TOptional<FString> SessionName,
        TOptional<int32> NumberOfPlayer,
        TOptional<FString> KeyId
    )
    {
        return SeasonName.Get(FString()) + ":" + SessionName.Get(FString());
    }

    FBallotAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FBallotAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FBallotAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FSignedBallot>> Result
    )
    {
        const FString CacheKey = Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(Self->SeasonName, Self->SessionName);
        const FString CacheParentKey = Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(Self->NamespaceName, Self->UserId(), Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>());
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SeasonRating::Model::FSignedBallot::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheKey, CacheParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SeasonRating::Model::FSignedBallotPtr Value;
                if (!Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FSignedBallot>(CacheParentKey, CacheKey, &Value))
                {
                    const auto Future = Self->Get(MakeShared<Gs2::SeasonRating::Request::FGetBallotRequest>());
                    Future->StartSynchronousTask();
                    Future->EnsureCompletion();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::SeasonRating::Model::FSignedBallot::TypeName, CacheParentKey, CacheKey, nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes));
                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "ballot")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                        Self->Gs2->Cache->Put(
                            Gs2::SeasonRating::Model::FSignedBallot::TypeName, CacheParentKey, CacheKey, Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes));
                    }
                }
                Self->Body = Value.IsValid() ? Value->GetBody() : TOptional<FString>();
                Self->Signature = Value.IsValid() ? Value->GetSignature() : TOptional<FString>();
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FBallotAccessTokenDomain::FModelTask>> FBallotAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBallotAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FBallotAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FSignedBallotPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SeasonRating::Domain::FGs2SeasonRatingDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QuerySeasonName = SeasonName;
        const TOptional<FString> QuerySessionName = SessionName;
        const TOptional<int32> QueryNumberOfPlayer = NumberOfPlayer;
        const TOptional<FString> QueryKeyId = KeyId;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset().Get(0)
            : 0;
        const FString RegisteredParentKey = FBallotDomain::CreateSignedCacheParentKey(
            QueryNamespaceName, RegisteredUserId, RegisteredTimeOffset
        );
        const FString RegisteredCacheKey = FBallotDomain::CreateCacheKey(QuerySeasonName, QuerySessionName);

        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FSignedBallot::TypeName,
            RegisteredParentKey,
            RegisteredCacheKey,
            [Callback](TSharedPtr<FGs2Object> Obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FSignedBallot>(Obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QuerySeasonName, QuerySessionName, QueryNumberOfPlayer, QueryKeyId, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId ||
                    TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FBallotAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QuerySeasonName,
                    QuerySessionName,
                    QueryNumberOfPlayer,
                    QueryKeyId
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBallotAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FSignedBallot::TypeName,
            Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(NamespaceName, UserId(), AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()),
            Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(SeasonName, SessionName),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
