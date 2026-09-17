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
 *
 * deny overwrite
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

    FBallotDomain::FBallotDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
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
        UserId(UserId),
        SeasonName(SeasonName),
        SessionName(SessionName),
        NumberOfPlayer(NumberOfPlayer),
        KeyId(KeyId),
        ParentKey(Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(NamespaceName, UserId))
    {
    }

    FBallotDomain::FBallotDomain(
        const FBallotDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        SeasonName(From.SeasonName),
        SessionName(From.SessionName),
        NumberOfPlayer(From.NumberOfPlayer),
        KeyId(From.KeyId),
        ParentKey(From.ParentKey)
    {

    }

    FBallotDomain::FGetTask::FGetTask(
        const TSharedPtr<FBallotDomain>& Self,
        const Request::FGetBallotByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBallotDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FSignedBallot>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSessionName(Self->SessionName)
            ->WithUserId(Self->UserId)
            ->WithNumberOfPlayer(Self->NumberOfPlayer)
            ->WithKeyId(Self->KeyId);
        const auto Future = Self->Client->GetBallotByUserId(Request);
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
                    Request->GetUserId(),
                    TOptional<int32>()
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

    TSharedPtr<FAsyncTask<FBallotDomain::FGetTask>> FBallotDomain::Get(
        Request::FGetBallotByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBallotDomain::CreateCacheParentKey(
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

    FString FBallotDomain::CreateSignedCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset
    )
    {
        return FString("seasonRating:") + NamespaceName.Get(FString()) + ":" + UserId.Get(FString()) + ":" +
            FString::FromInt(TimeOffset.Get(0)) + ":SignedBallot";
    }

    FString FBallotDomain::CreateCacheKey(
        TOptional<FString> SeasonName,
        TOptional<FString> SessionName,
        TOptional<int32> NumberOfPlayer,
        TOptional<FString> KeyId
    )
    {
        return SeasonName.Get(FString()) + ":" + SessionName.Get(FString());
    }

    FBallotDomain::FModelTask::FModelTask(
        const TSharedPtr<FBallotDomain> Self
    ): Self(Self)
    {

    }

    FBallotDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBallotDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FSignedBallot>> Result
    )
    {
        const FString CacheKey = Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateCacheKey(Self->SeasonName, Self->SessionName);
        const FString CacheParentKey = Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(Self->NamespaceName, Self->UserId);
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SeasonRating::Model::FSignedBallot::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheKey, CacheParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SeasonRating::Model::FSignedBallotPtr Value;
                if (!Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FSignedBallot>(CacheParentKey, CacheKey, &Value))
                {
                    const auto Future = Self->Get(MakeShared<Gs2::SeasonRating::Request::FGetBallotByUserIdRequest>());
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

    TSharedPtr<FAsyncTask<FBallotDomain::FModelTask>> FBallotDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBallotDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FBallotDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FSignedBallotPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SeasonRating::Domain::FGs2SeasonRatingDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QuerySeasonName = SeasonName;
        const TOptional<FString> QuerySessionName = SessionName;
        const TOptional<int32> QueryNumberOfPlayer = NumberOfPlayer;
        const TOptional<FString> QueryKeyId = KeyId;
        const FString RegisteredParentKey = FBallotDomain::CreateSignedCacheParentKey(QueryNamespaceName, QueryUserId);
        const FString RegisteredCacheKey = FBallotDomain::CreateCacheKey(QuerySeasonName, QuerySessionName);

        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FSignedBallot::TypeName,
            RegisteredParentKey,
            RegisteredCacheKey,
            [Callback](TSharedPtr<FGs2Object> Obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FSignedBallot>(Obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySessionName, QueryNumberOfPlayer, QueryKeyId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FBallotDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
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

    void FBallotDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FSignedBallot::TypeName,
            Gs2::SeasonRating::Domain::Model::FBallotDomain::CreateSignedCacheParentKey(NamespaceName, UserId),
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
