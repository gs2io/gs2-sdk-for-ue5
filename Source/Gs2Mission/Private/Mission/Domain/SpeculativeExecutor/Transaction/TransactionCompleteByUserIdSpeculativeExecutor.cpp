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

#include "Mission/Domain/SpeculativeExecutor/Transaction/CompleteByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Mission::Domain::Transaction::SpeculativeExecutor
{
    FString FCompleteByUserIdSpeculativeExecutor::Action() {
        return "Gs2Mission:CompleteByUserId";
    }

    FCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result)
    {
        const auto Future = Domain->Mission->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : ""
            )->MissionGroupModel(
                Request->GetMissionGroupName().IsSet() ? *Request->GetMissionGroupName() : ""
            )->MissionTaskModel(
                Request->GetMissionTaskName().IsSet() ? *Request->GetMissionTaskName() : ""
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([]{});
            return nullptr;
        }

        Service->OnIssueTransaction.Broadcast(
            MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                AccessToken,
                [this]{
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
                    Arr->Add(
                        MakeShared<Core::Model::FConsumeAction>()
                        ->WithAction(TOptional<FString>("Gs2Mission:ReceiveByUserId^"))
                        ->WithRequest(TOptional<FString>(
                            [this]
                            {
                                FString Body("");
                                const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
                                FJsonSerializer::Serialize(
                                MakeShared<Gs2::Mission::Request::FReceiveByUserIdRequest>()
                                        ->WithNamespaceName(Request->GetNamespaceName())
                                        ->WithUserId(AccessToken->GetUserId())
                                        ->WithMissionGroupName(Request->GetMissionGroupName())
                                        ->WithMissionTaskName(Request->GetMissionTaskName())
                                        ->ToJson().ToSharedRef(), Writer);
                                return Body;
                            }()
                        ))
                    );
                    return Arr;
                }(),
                Item->GetCompleteAcquireActions(),
                1.0
            )
        );

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteByUserIdSpeculativeExecutor::FCommitTask>> FCompleteByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
