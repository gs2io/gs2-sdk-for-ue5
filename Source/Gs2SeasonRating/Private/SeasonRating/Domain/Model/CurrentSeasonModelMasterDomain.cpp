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

#include "SeasonRating/Domain/Model/CurrentSeasonModelMaster.h"
#include "SeasonRating/Domain/Model/Namespace.h"
#include "SeasonRating/Domain/Model/MatchSession.h"
#include "SeasonRating/Domain/Model/SeasonModelMaster.h"
#include "SeasonRating/Domain/Model/SeasonModel.h"
#include "SeasonRating/Domain/Model/CurrentSeasonModelMaster.h"
#include "SeasonRating/Domain/Model/Ballot.h"
#include "SeasonRating/Domain/Model/BallotAccessToken.h"
#include "SeasonRating/Domain/Model/Vote.h"
#include "SeasonRating/Domain/Model/User.h"
#include "SeasonRating/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SeasonRating::Domain::Model
{

    FCurrentSeasonModelMasterDomain::FCurrentSeasonModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SeasonRating::FGs2SeasonRatingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentSeasonModelMaster"
        ))
    {
    }

    FCurrentSeasonModelMasterDomain::FCurrentSeasonModelMasterDomain(
        const FCurrentSeasonModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentSeasonModelMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentSeasonModelMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentSeasonModelMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentSeasonModelMasterDomain::FExportMasterTask>> FCurrentSeasonModelMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentSeasonModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
        const Request::FGetCurrentSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentSeasonModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentSeasonModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentSeasonModelMasterDomain::FGetTask>> FCurrentSeasonModelMasterDomain::Get(
        Request::FGetCurrentSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentSeasonModelMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
        const Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentSeasonModelMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const FPreUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentSeasonModelMasterDomain::FPreUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Self->UploadUrl = Domain->UploadUrl = ResultModel->GetUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentSeasonModelMasterDomain::FPreUpdateTask>> FCurrentSeasonModelMasterDomain::PreUpdate(
        Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPreUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentSeasonModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
        const Request::FUpdateCurrentSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentSeasonModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentSeasonModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentSeasonModelMasterDomain::FUpdateTask>> FCurrentSeasonModelMasterDomain::Update(
        Request::FUpdateCurrentSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentSeasonModelMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentSeasonModelMasterDomain>& Self,
        const Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentSeasonModelMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentSeasonModelMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentSeasonModelMasterDomain::FUpdateFromGitHubTask>> FCurrentSeasonModelMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentSeasonModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentSeasonModelMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentSeasonModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentSeasonModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentSeasonModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentSeasonModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>(
            Self->ParentKey,
            Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::SeasonRating::Request::FGetCurrentSeasonModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::SeasonRating::Model::FCurrentSeasonModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "currentSeasonModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>(
                Self->ParentKey,
                Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentSeasonModelMasterDomain::FModelTask>> FCurrentSeasonModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentSeasonModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCurrentSeasonModelMasterDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FCurrentSeasonModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FCurrentSeasonModelMaster::TypeName,
            ParentKey,
            Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FCurrentSeasonModelMaster>(obj));
            }
        );
    }

    void FCurrentSeasonModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FCurrentSeasonModelMaster::TypeName,
            ParentKey,
            Gs2::SeasonRating::Domain::Model::FCurrentSeasonModelMasterDomain::CreateCacheKey(
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

