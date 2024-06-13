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

#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
#include "Matchmaking/Domain/Model/RatingModelMaster.h"
#include "Matchmaking/Domain/Model/RatingModel.h"
#include "Matchmaking/Domain/Model/CurrentModelMaster.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"
#include "Matchmaking/Domain/Model/Season.h"
#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
#include "Matchmaking/Domain/Model/SeasonModel.h"
#include "Matchmaking/Domain/Model/SeasonModelMaster.h"
#include "Matchmaking/Domain/Model/SeasonGathering.h"
#include "Matchmaking/Domain/Model/SeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGathering.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("matchmaking:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("matchmaking:Namespace");
                const auto Key = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("matchmaking:Namespace");
                const auto Key = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("matchmaking:Namespace");
                const auto Key = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Matchmaking::Model::FNamespace::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRatingModelMasterTask::FCreateRatingModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateRatingModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRatingModelMasterTask::FCreateRatingModelMasterTask(
        const FCreateRatingModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRatingModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateRatingModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RatingModelMaster"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FRatingModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRatingModelMasterTask>> FNamespaceDomain::CreateRatingModelMaster(
        Request::FCreateRatingModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRatingModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FVoteTask::FVoteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FVoteRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FVoteTask::FVoteTask(
        const FVoteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FVoteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->Vote(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetUserId(),
                    "Ballot"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRatingName(),
                    ResultModel->GetItem()->GetGatheringName(),
                    ResultModel->GetItem()->GetNumberOfPlayer().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetNumberOfPlayer()) : TOptional<FString>(),
                    RequestModel->GetKeyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FBallot::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FBallotDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetRatingName(),
            ResultModel->GetItem()->GetGatheringName(),
            ResultModel->GetItem()->GetNumberOfPlayer(),
            Request->GetKeyId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FVoteTask>> FNamespaceDomain::Vote(
        Request::FVoteRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVoteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FVoteMultipleTask::FVoteMultipleTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FVoteMultipleRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FVoteMultipleTask::FVoteMultipleTask(
        const FVoteMultipleTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FVoteMultipleTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->VoteMultiple(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetUserId(),
                    "Ballot"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FBallotDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRatingName(),
                    ResultModel->GetItem()->GetGatheringName(),
                    ResultModel->GetItem()->GetNumberOfPlayer().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetNumberOfPlayer()) : TOptional<FString>(),
                    RequestModel->GetKeyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FBallot::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FBallotDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetRatingName(),
            ResultModel->GetItem()->GetGatheringName(),
            ResultModel->GetItem()->GetNumberOfPlayer(),
            Request->GetKeyId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FVoteMultipleTask>> FNamespaceDomain::VoteMultiple(
        Request::FVoteMultipleRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVoteMultipleTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateSeasonModelMasterTask::FCreateSeasonModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateSeasonModelMasterTask::FCreateSeasonModelMasterTask(
        const FCreateSeasonModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateSeasonModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateSeasonModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SeasonModelMaster"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FSeasonModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateSeasonModelMasterTask>> FNamespaceDomain::CreateSeasonModelMaster(
        Request::FCreateSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateSeasonModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain> FNamespaceDomain::CurrentModelMaster(
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FCurrentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIteratorPtr FNamespaceDomain::RatingModels(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRatingModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FRatingModel::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RatingModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeRatingModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FRatingModel::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RatingModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingModelDomain> FNamespaceDomain::RatingModel(
        const FString RatingName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FRatingModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelMastersIteratorPtr FNamespaceDomain::RatingModelMasters(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRatingModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FRatingModelMaster::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RatingModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeRatingModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FRatingModelMaster::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RatingModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain> FNamespaceDomain::RatingModelMaster(
        const FString RatingName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName)
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FVoteDomain> FNamespaceDomain::Vote(
        const FString RatingName,
        const FString GatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FVoteDomain>(
            Gs2,
            Service,
            NamespaceName,
            RatingName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RatingName),
            GatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GatheringName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonModelsIteratorPtr FNamespaceDomain::SeasonModels(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeSeasonModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FSeasonModel::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "SeasonModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeSeasonModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FSeasonModel::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "SeasonModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonModelDomain> FNamespaceDomain::SeasonModel(
        const FString SeasonName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            SeasonName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonModelMastersIteratorPtr FNamespaceDomain::SeasonModelMasters(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeSeasonModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FSeasonModelMaster::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "SeasonModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeSeasonModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FSeasonModelMaster::TypeName,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "SeasonModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain> FNamespaceDomain::SeasonModelMaster(
        const FString SeasonName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            SeasonName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonName)
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("matchmaking:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FNamespace> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FNamespace>(
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FNamespace>(
                ParentKey,
                Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FNamespace>(obj));
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

