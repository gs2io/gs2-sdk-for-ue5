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

#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FCompleteAccessTokenDomain::FCompleteAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> MissionGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        MissionGroupName(MissionGroupName),
        ParentKey(Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Complete"
        ))
    {
    }

    FCompleteAccessTokenDomain::FCompleteAccessTokenDomain(
        const FCompleteAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FCompleteAccessTokenDomain::FCompleteTask::FCompleteTask(
        const TSharedPtr<FCompleteAccessTokenDomain> Self,
        const Request::FCompleteRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteAccessTokenDomain::FCompleteTask::FCompleteTask(
        const FCompleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FCompleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->Complete(
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
        if (!*ResultModel->GetAutoRunStampSheet())
        {
            const auto StampSheet = MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                Self->Cache,
                Self->JobQueueDomain,
                Self->Session,
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId(),
                Self->StampSheetConfiguration
            );
            const auto Future3 = StampSheet->Run();
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return MakeShared<Core::Model::FTransactionError<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>(
                    Future3->GetTask().Error()->GetErrors(),
                    [&]() -> TSharedPtr<FAsyncTask<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>
                    {
                        return MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                            Self->Cache,
                            Self->JobQueueDomain,
                            Self->Session,
                            *ResultModel->GetStampSheet(),
                            *ResultModel->GetStampSheetEncryptionKeyId(),
                            Self->StampSheetConfiguration
                        )->Run();
                    }
                );
            }
            Future3->EnsureCompletion();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FCompleteTask>> FCompleteAccessTokenDomain::Complete(
        Request::FCompleteRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCompleteTask>>(this->AsShared(), Request);
    }

    FCompleteAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FCompleteAccessTokenDomain> Self,
        const Request::FGetCompleteRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->GetComplete(
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
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Complete"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetMissionGroupName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetNextResetAt().IsSet() && *ResultModel->GetItem()->GetNextResetAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetNextResetAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FGetTask>> FCompleteAccessTokenDomain::Get(
        Request::FGetCompleteRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FCompleteAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MissionGroupName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            ChildType;
    }

    FString FCompleteAccessTokenDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString() +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FCompleteAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FCompleteAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FCompleteAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Mission::Model::FComplete>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                Self->MissionGroupName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetCompleteRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "complete")
                    {
                        Self->Cache->Delete(
                            Gs2::Mission::Model::FComplete::TypeName,
                            Self->ParentKey,
                            Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                                Self->MissionGroupName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Mission::Model::FComplete>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    Self->MissionGroupName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FModelTask>> FCompleteAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCompleteAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

