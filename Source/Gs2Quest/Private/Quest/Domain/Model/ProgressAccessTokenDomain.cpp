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

#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FProgressAccessTokenDomain::FProgressAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Progress"
        ))
    {
    }

    FProgressAccessTokenDomain::FProgressAccessTokenDomain(
        const FProgressAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FProgressAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FProgressAccessTokenDomain> Self,
        const Request::FGetProgressRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FProgress>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetProgress(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetQuestGroup() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "QuestGroupModel"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheKey(
                    ResultModel->GetQuestGroup()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetQuestGroup(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetQuest() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Gs2::Quest::Model::FQuestModel::GetQuestGroupNameFromGrn(*ResultModel->GetItem()->GetQuestModelId()),
                    "QuestModel"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                    ResultModel->GetQuest()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetQuest(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FGetTask>> FProgressAccessTokenDomain::Get(
        Request::FGetProgressRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FProgressAccessTokenDomain::FEndTask::FEndTask(
        const TSharedPtr<FProgressAccessTokenDomain> Self,
        const Request::FEndRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressAccessTokenDomain::FEndTask::FEndTask(
        const FEndTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FEndTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->End(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Cache->Delete(Gs2::Quest::Model::FProgress::TypeName, ParentKey, Key);
            }
            Self->Cache->Delete(
                Gs2::Quest::Model::FCompletedQuestList::TypeName,
                Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "CompletedQuestList"
                ),
                Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    Gs2::Quest::Model::FQuestModel::GetQuestGroupNameFromGrn(*ResultModel->GetItem()->GetQuestModelId())
                )
            );
            Self->Cache->ClearListCache(
                Gs2::Quest::Model::FCompletedQuestList::TypeName,
                Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "CompletedQuestList"
                )
            );
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

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FEndTask>> FProgressAccessTokenDomain::End(
        Request::FEndRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEndTask>>(this->AsShared(), Request);
    }

    FProgressAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FProgressAccessTokenDomain> Self,
        const Request::FDeleteProgressRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteProgress(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Cache->Delete(Gs2::Quest::Model::FProgress::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FDeleteTask>> FProgressAccessTokenDomain::Delete(
        Request::FDeleteProgressRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FProgressAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FProgressAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FProgressAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FProgressAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FProgressAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FProgress>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Quest::Model::FProgress>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetProgressRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "progress")
                    {
                        Self->Cache->Delete(
                            Gs2::Quest::Model::FProgress::TypeName,
                            Self->ParentKey,
                            Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Quest::Model::FProgress>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FModelTask>> FProgressAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProgressAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

